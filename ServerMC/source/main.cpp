#include <crow.h>
#include "Map.h"
#include "PlayerObject.h"
#include "BulletObject.h"
#include "DatabaseManager.h"
#include <algorithm>
#include <mutex>
#include <memory>
#include <chrono>

#include <chrono>
#include <cstdlib>
#include <ctime>

import utils;
using namespace http;

const std::pair<int, int>* findClientByID(std::vector<std::pair<int, int>>& Clients, const int clientID) {
	for (auto& client : Clients) {
		if (client.first == clientID) {
			return &client;
		}
	}
	return nullptr;
}

int getIntFromArgs(std::unordered_map<std::string, std::string>& bodyArgs, const std::string& key) {
	auto clientIter = bodyArgs.find(key);

	if (clientIter == bodyArgs.end()) {
		throw std::runtime_error("Key not found in request parameters");
	}

	try {
		return std::stoi(clientIter->second);
	}
	catch (const std::invalid_argument& e) {
		throw std::runtime_error("Invalid integer format");
	}
	catch (const std::out_of_range& e) {
		throw std::runtime_error("Integer out of range");
	}
	return 1;
}

int main(int argc, char* args[])
{
	std::srand(std::time(nullptr));

	std::vector< std::pair<int, int> > Clients;
	std::vector<
		std::tuple<
		std::map<std::string, std::shared_ptr<GameObject>>, //Objects in the room
		std::array<int, 4>, //Clients connected to room
		Map //Map of the room
		>
	> Rooms;
	crow::SimpleApp app;
	std::mutex DataMutex;
	DatabaseManager databaseManager;

	CROW_ROUTE(app, "/player_input").methods(crow::HTTPMethod::PUT)
		([&Clients, &Rooms, &DataMutex](const crow::request& req) {
		DataMutex.lock();
		auto bodyArgs = parseUrlArgs(req.body);
		auto end = bodyArgs.end();

		if (!req.url_params.get("clientID")) {
			DataMutex.unlock();
			return crow::response(500);
		}

		std::string clientID = req.url_params.get("clientID");
		const std::pair<int, int>* curClient = findClientByID(Clients, std::stoi(clientID));
		if (curClient == nullptr) {
			DataMutex.unlock();
			return crow::response(500);
		}

		int clientUpDown = getIntFromArgs(bodyArgs, "upDown");
		int clientleftRight = getIntFromArgs(bodyArgs, "leftRight");
		bool clientShot = getIntFromArgs(bodyArgs, "Shoot");

		if (clientUpDown != 0) clientleftRight = 0;

		auto& curRoom = Rooms[curClient->second];
		auto& gameObjects = std::get<0>(curRoom);

		auto it = gameObjects.find("Player" + std::to_string(curClient->first));
		if (it == gameObjects.end()) {
			DataMutex.unlock();
			return crow::response(500);
		}
		Map& curMap = std::get<2>(curRoom);

		std::shared_ptr<PlayerObject> plrObj = std::dynamic_pointer_cast<PlayerObject>(it->second);

		if (!plrObj->getAlive()) {
			DataMutex.unlock();
			return crow::response(500);
		}

		plrObj->setVel(Vector2D((float)clientUpDown, (float)clientleftRight));
		plrObj->Update(curMap, clientShot, gameObjects);

		DataMutex.unlock();
		return crow::response(201);
			});

	CROW_ROUTE(app, "/join_game")
		([&Clients, &Rooms, &DataMutex, &databaseManager](const crow::request& req) {
		DataMutex.lock();
		crow::json::wvalue response;

		std::string clientUser = req.url_params.get("clientUser");

		int clientID = databaseManager.GetUserIdByUsername(clientUser);
		int roomID = -1;

		auto clientIt = std::find_if(Clients.begin(), Clients.end(), [&clientID](std::pair<int, int>& client) {
			return client.first == clientID;
			});
		if (clientIt != Clients.end()) {
			DataMutex.unlock();
			response["clientConnected"] = true;
			return response;
		}

		bool roomIsFull = true;
		std::array<int, 4>* curClients = nullptr;
		for (int i = 0; i < Rooms.size(); ++i) {
			curClients = &std::get<1>(Rooms[i]);
			for (int j = 0; j < curClients->size(); ++j) {
				if ((*curClients)[j] == 0) {
					roomIsFull = false;
					(*curClients)[j] = clientID;
					roomID = i;
					break;
				}
			}
		}
		if (roomIsFull == true) {
			roomID = Rooms.size();
			Rooms.emplace_back(std::map<std::string, std::shared_ptr<GameObject>>(), std::array<int, 4>{0, 0, 0, 0}, Map(30, 30));
			std::get<2>(Rooms[roomID]).createRandomMap();
			std::get<1>(Rooms[roomID])[0] = clientID;
		}
		Clients.emplace_back(clientID, roomID);
		response["clientID"] = clientID;

		std::pair<int, int> mapSize = std::get<2>(Rooms[roomID]).getSize();
		Vector2D spawnPos = Vector2D(0, 0);
		switch ((clientID - 1) % 4)
		{
		case 0:
			spawnPos = Vector2D(0, 0);
			break;
		case 1:
			spawnPos = Vector2D(0, mapSize.second - 1);
			break;
		case 2:
			spawnPos = Vector2D(mapSize.first - 1, 0);
			break;
		case 3:
			spawnPos = Vector2D(mapSize.first - 1, mapSize.second - 1);
			break;
		}

		auto& gameObjects = std::get<0>(Rooms[roomID]);
		gameObjects.emplace("Player" + std::to_string(clientID),
			std::make_shared<PlayerObject>(
				spawnPos,
				std::to_string((clientID - 1) % 4),
				databaseManager.GetUserFirerate(clientID)
			));

		DataMutex.unlock();
		return response;
			});

	CROW_ROUTE(app, "/get_map")
		([&Rooms, &Clients, &DataMutex](const crow::request& req) {
		DataMutex.lock();

		if (!req.url_params.get("clientID")) {
			DataMutex.unlock();
			return crow::response(400);
		}

		std::string clientID = req.url_params.get("clientID");
		const std::pair<int, int>* curClient = findClientByID(Clients, std::stoi(clientID));
		if (curClient == nullptr) {
			DataMutex.unlock();
			return crow::response(400);
		}

		auto& curRoom = Rooms[curClient->second];
		auto& gameObjects = std::get<0>(curRoom);
		Map& curMap = std::get<2>(curRoom);

		
		static auto lastSpecialSpawn = std::chrono::steady_clock::now();
		auto now = std::chrono::steady_clock::now();

		
		auto diffSec = std::chrono::duration_cast<std::chrono::seconds>(now - lastSpecialSpawn).count();
		if (diffSec >= 60) {
			

			
			std::pair<int, int> mapSize = curMap.getSize();

			
			int rx = std::rand() % mapSize.first;   
			int ry = std::rand() % mapSize.second;  

			
			if (curMap.getPositionValue(rx, ry) == CellType::FREE_SPACE) {
				
				curMap.setPositionValue(rx, ry, CellType::SPECIAL_ITEM);

				// Resetăm timerul
				//lastSpecialSpawn = now;
			}
		}

		std::pair<int, int> curSize = curMap.getSize();
		auto mapData = curMap.getMap();

		crow::json::wvalue jsonMap;
		for (int y = 0; y < curSize.first; ++y) {
			for (int x = 0; x < curSize.second; ++x) {
				jsonMap["map"][y][x] = mapData[y][x];
			}
		}

		for (const auto& [objID, object] : gameObjects) {
			Vector2D objPos = object->getPos();
			if (std::shared_ptr<PlayerObject> plrObj = std::dynamic_pointer_cast<PlayerObject>(object)) {
				if (plrObj->getAlive()) {
					jsonMap["map"][objPos.getX()][objPos.getY()] = CellType::PLAYER;
					jsonMap[
						std::to_string((int)objPos.getX()) + std::to_string((int)objPos.getY())
					] = crow::json::wvalue::list{ std::stoi(std::string(1, objID.back())), plrObj->getID(), plrObj->getFacing().getX(), plrObj->getFacing().getY() };
				}
			}
			else if (std::shared_ptr<Bullet> bltObj = std::dynamic_pointer_cast<Bullet>(object)) {
				bltObj->Update(curMap, gameObjects);
				if (!bltObj->getState())
					jsonMap["map"][objPos.getX()][objPos.getY()] = CellType::BULLET;
			}
		}

		for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
			if (std::shared_ptr<Bullet> bltObj = std::dynamic_pointer_cast<Bullet>(it->second)) {
				if (bltObj->getState()) {
					it = gameObjects.erase(it);
					continue;
				}
			}
			else if (std::shared_ptr<PlayerObject> plrObj = std::dynamic_pointer_cast<PlayerObject>(it->second)) {
				if (!plrObj->getAlive()) {
					it = gameObjects.erase(it);
					continue;
				}
			}
			++it;
		}

		DataMutex.unlock();
		return crow::response(jsonMap);
			});

	CROW_ROUTE(app, "/leave_game").methods(crow::HTTPMethod::PUT)
		([&Clients, &Rooms, &DataMutex](const crow::request& req) {
		DataMutex.lock();

		auto bodyArgs = parseUrlArgs(req.body);
		auto end = bodyArgs.end();
		auto clientIter = bodyArgs.find("clientID");

		if (clientIter != end) {
			int curClientID = std::stoi(clientIter->second);
			std::pair<int, int>* curClient = nullptr;

			auto clientIt = std::find_if(Clients.begin(), Clients.end(), [curClientID, &curClient](std::pair<int, int>& client) {
				if (client.first == curClientID)
					curClient = &client;
				return client.first == curClientID;
				});

			if (clientIt == Clients.end()) {
				DataMutex.unlock();
				return crow::response(400);
			}

			auto& curRoom = Rooms[curClient->second];
			auto& gameObjects = std::get<0>(curRoom);

			auto objIt = gameObjects.find("Player" + std::to_string(curClientID));
			if (objIt != gameObjects.end()) {
				gameObjects.erase(objIt);
			}

			std::array<int, 4>& connectedClients = std::get<1>(curRoom);
			for (int i = 0; i < connectedClients.size(); ++i) {
				if (connectedClients[i] == curClientID) {
					connectedClients[i] = 0;
					break;
				}
			}

			Clients.erase(clientIt);
		}

		DataMutex.unlock();
		return crow::response(204);
			});

	//load the database
	databaseManager.CreateDatabase("gamedb.sqlite");

	//create a first initial room
	Rooms.emplace_back(std::map<std::string, std::shared_ptr<GameObject>>(), std::array<int, 4>{0, 0, 0, 0}, Map(30, 30));
	std::get<2>(Rooms[0]).createRandomMap();

	app.loglevel(crow::LogLevel::Warning);

	app.port(18080).multithreaded().run();

	return 0;
}
