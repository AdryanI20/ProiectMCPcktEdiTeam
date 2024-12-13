//#include <iostream>
//#include <string>
//#include <cpr/cpr.h>
//#include <crow.h>
//#include <windows.h>
//
//
//void move_player(int dx, int dy) {
//    cpr::Response r = cpr::Put(cpr::Url{ "http://localhost:18080/move_player" },
//        cpr::Payload{ 
//            {"dx", std::to_string(dx)}, 
//            {"dy", std::to_string(dy)} 
//        });
//    if (r.status_code != 204) {
//        std::cout << "Failed to move player!" << std::endl;
//    }
//}
//
//void get_player_position() {
//    cpr::Response r = cpr::Get(cpr::Url{ "http://localhost:18080/get_player_position" });
//    if (r.status_code == 200) {
//        auto json = crow::json::load(r.text);
//        auto x = json["x"].i();
//        auto y = json["y"].i();
//        std::cout << x << " " << y << std::endl;
//    }
//    else {
//        std::cout << "Failed to get player position!" << std::endl;
//    }
//}
//
//int main() {
//    int player_x = 0, player_y = 0;
//
//    bool running = true;
//    while (running) {
//        if (GetAsyncKeyState(69) & 0x8000) {
//            player_x += 1;
//            player_y += 2;
//            move_player(player_x, player_y);
//        }
//
//        get_player_position();
//        Sleep(6);
//    }
//
//    return 0;
//}