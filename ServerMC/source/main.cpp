#include <crow.h>
#include "Map.h"
#include "PlayerObject.h"
#include <algorithm>
import utils;
using namespace http;

typedef std::map<std::string, GameObject*>::iterator objs_it;

int main(int argc, char* args[])
{
    std::map<std::string, GameObject*> gameObjects; //same for players and their objects

    Map* cur_map = new Map(30, 30);
    cur_map->createRandomMap();
    uint16_t clientIDCounter = 0;
    std::vector<uint16_t> Clients;
    crow::SimpleApp app;

    //Change to account verification
    //CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::PUT)(
        //[]() {
            //if 

        //});

    CROW_ROUTE(app, "/join_game")
        ([&Clients, &gameObjects, cur_map, &clientIDCounter]() {
        uint16_t clientID = clientIDCounter++;
        Clients.push_back(clientID); //[clientID] = clientID;
        crow::json::wvalue response;
        response["clientID"] = clientID;

        gameObjects.emplace("Player"+std::to_string(clientID),
            new PlayerObject(
                0,
                0,
                cur_map->getPositionValue(0, 0),
                0,
                "Player" + std::to_string(clientID)
            ));

        return response;
            });

    CROW_ROUTE(app, "/get_map")([cur_map]() {
        std::string binary_map;
        std::pair<int, int> curSize = cur_map->getSize();
        binary_map.reserve(curSize.first * curSize.second);

        for (const auto& row : cur_map->getMap()) {
            for (const auto& cell : row) {
                binary_map.push_back(static_cast<uint8_t>(cell));
            }
        }

        return crow::response(binary_map);
    });

    CROW_ROUTE(app, "/leave_game").methods(crow::HTTPMethod::PUT) ([&Clients](const crow::request& req) {
        auto bodyArgs = parseUrlArgs(req.body);
        auto end = bodyArgs.end();
        auto clientIter = bodyArgs.find("clientID");
        uint16_t curClientID;
        if (clientIter != end) {
            curClientID = std::stoi(clientIter->second);
            auto ClientsIt = std::find(Clients.begin(), Clients.end(), curClientID);
            if (ClientsIt != Clients.end())
                Clients.erase(ClientsIt);
        }

        return crow::response(204);
    });

    app.port(18080).multithreaded().run();

    return 0;
}
