#include <crow.h>
#include "Map.h"
#include "PlayerObject.h"
#include <algorithm>
#include "DatabaseManager.h"
#include <filesystem>

import utils;
using namespace http;

typedef std::map<std::string, GameObject*>::iterator objs_it;

int main(int argc, char* args[])
{
    std::map<std::string, GameObject*> gameObjects; //same for players and their objects

    Map* cur_map = new Map(30, 30);
    cur_map->createRandomMap();
    int clientIDCounter = 0;
    std::vector<int> Clients;
    std::vector<std::array<int, 4>> Rooms;
    crow::SimpleApp app;

    //Change to account verification
    //CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::PUT)(
        //[]() {
            //if 

        //});

    CROW_ROUTE(app, "/player_input").methods(crow::HTTPMethod::PUT)
        ([&Clients, &gameObjects, cur_map](const crow::request& req) {
        auto bodyArgs = parseUrlArgs(req.body);
        auto end = bodyArgs.end();

        auto clientIter = bodyArgs.find("clientID");
        int curClientID;
        if (clientIter == end) return crow::response(500);
        curClientID = std::stoi(clientIter->second);
        
        clientIter = bodyArgs.find("upDown");
        int clientUpDown;
        if (clientIter == end) return crow::response(500);
        clientUpDown = std::stoi(clientIter->second);

        clientIter = bodyArgs.find("leftRight");
        int clientleftRight;
        if (clientIter == end) return crow::response(500);
        clientleftRight = std::stoi(clientIter->second);

        clientIter = bodyArgs.find("Shoot");
        bool clientShot;
        if (clientIter == end) return crow::response(500);
        clientShot = std::stoi(clientIter->second);

        auto ClientsIt = std::find(Clients.begin(), Clients.end(), curClientID);
        if (ClientsIt == Clients.end()) return crow::response(500);

        PlayerObject* PlrObj = dynamic_cast<PlayerObject *>(gameObjects["Player" + std::to_string(curClientID)]);
        PlrObj->setVel(Vector2D((float)clientUpDown, (float)clientleftRight));
        PlrObj->Update(cur_map, clientShot, gameObjects);

        return crow::response(201);
        });

    CROW_ROUTE(app, "/join_game")
        ([&Clients, &gameObjects, cur_map, &clientIDCounter, &Rooms]() {
        int clientID = clientIDCounter++;
        Clients.push_back(clientID);
        /*for (int i = 0; i < Rooms.size(); ++i) {
            for (int j = 0; j < Rooms[i].size(); ++j) {
                std::cout << vectorOfArrays[i][j] << " ";
            }
        }*/
        crow::json::wvalue response;
        response["clientID"] = clientID;

        gameObjects.emplace("Player"+std::to_string(clientID),
            new PlayerObject(
                0,
                0,
                std::to_string((clientID%4)+1)
            ));

        return response;
        });

    CROW_ROUTE(app, "/get_map")
        ([cur_map, &gameObjects]() {

        std::pair<int, int> curSize = cur_map->getSize();
        auto mapData = cur_map->getMap();

        crow::json::wvalue jsonMap;
        for (int y = 0; y < curSize.first; ++y) {
            for (int x = 0; x < curSize.second; ++x) {
                jsonMap["map"][y][x] = mapData[y][x];
            }
        }

        for (const auto& [_, object] : gameObjects) {
            Vector2D objPos = object->getPos();
            if (auto plrObj = dynamic_cast<PlayerObject*>(object)) {
                jsonMap["map"][objPos.getX()][objPos.getY()] = CellType::PLAYER;
                jsonMap[
                    std::to_string((int)objPos.getX()) + std::to_string((int)objPos.getY())
                ] = crow::json::wvalue::list{ plrObj->getID(), plrObj->getFacing().getX(), plrObj->getFacing().getY() };
            };
            //TODO: other objects
        }

        return crow::response(jsonMap);
    });

    CROW_ROUTE(app, "/leave_game").methods(crow::HTTPMethod::PUT) 
        ([&Clients](const crow::request& req) {

        auto bodyArgs = parseUrlArgs(req.body);
        auto end = bodyArgs.end();
        auto clientIter = bodyArgs.find("clientID");
        int curClientID;
        if (clientIter != end) {
            curClientID = std::stoi(clientIter->second);
            auto ClientsIt = std::find(Clients.begin(), Clients.end(), curClientID);
            if (ClientsIt != Clients.end())
                Clients.erase(ClientsIt);
        }

        return crow::response(204);
    });

    app.port(18080).multithreaded().run();

    DatabaseManager dbManager;
    const std::string databaseFile = "BD.sqLite";

    if (std::filesystem::exists(databaseFile)) {
        std::cout << "Database already exists. Skipping creation.\n";
    }
    else {
        std::cout << "Database does not exist. Creating a new one...\n";

        dbManager.CreateDatabase(databaseFile);
        if (std::filesystem::exists(databaseFile))
        {
            std::cout << "Database created successfully.\n";
        }
        
    }
    return 0;
}
