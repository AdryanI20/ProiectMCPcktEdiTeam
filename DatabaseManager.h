#pragma once
#pragma once
#include <string>
#include <sqlite3.h>
#include "Player.h"

class DatabaseManager {
public:
    DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

    bool addPlayer(const Player& player);
    bool updatePlayer(const Player& player);
    Player getPlayer(int id);
    bool deletePlayer(int id);
    void closeDatabase();

private:
    sqlite3* m_db;
    bool executeQuery(const std::string& query);
};
