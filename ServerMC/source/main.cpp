#include <crow.h>
//using namespace http;

struct Player {
    int x, y;
    Player(int x, int y) : x(x), y(y) {}
};

int main(int argc, char* args[])
{
    uint16_t clientIDCounter = 0;
    std::unordered_map<int, Player> Clients;
    crow::SimpleApp app;

    CROW_ROUTE(app, "/join_game")
        ([&Clients]() {
        static int clientIDCounter = 0;
        int clientID = clientIDCounter++;
        Clients[clientID] = Player(0, 0);
        crow::json::wvalue response;
        response["clientID"] = clientID;
        return response;
            });

    app.port(18080).multithreaded().run();

    return 0;
}
