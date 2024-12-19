#include <iostream>
#include <sqlite3.h>
#include "Player.h"

void createDatabase()
{
    sqlite3* db;
    char* errorMessage;

    int exit = sqlite3_open("players.db", &db);
    if (exit)
    {
        std::cerr << "Eroare la deschiderea bazei de date: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    else
    {
        std::cout << "Baza de date a fost creata/deschisa cu succes." << std::endl;
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS Player ("
        "ID INT PRIMARY KEY NOT NULL, "
        "Team INT NOT NULL, "
        "Name TEXT NOT NULL, "
        "Points INT NOT NULL, "
        "Score INT NOT NULL);";

    exit = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errorMessage);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Eroare la crearea tabelei: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else
    {
        std::cout << "Tabela Player a fost creata cu succes." << std::endl;
    }

    sqlite3_close(db);
}

// Inserarea unui jucator în baza de date
void insertPlayer(const Player& player)
{
    sqlite3* db;
    sqlite3_open("players.db", &db);

    std::string sql = "INSERT INTO Player (ID, Team, Name, Points, Score) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, player.getId());
    sqlite3_bind_int(stmt, 2, player.getTeam());
    sqlite3_bind_text(stmt, 3, player.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, player.getPoints());
    sqlite3_bind_int(stmt, 5, player.getScore());

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Eroare la inserare: " << sqlite3_errmsg(db) << std::endl;
    }
    else
    {
        std::cout << "Jucator inserat cu succes." << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// Ob?inerea unui jucator din baza de date pe baza ID-ului
Player getPlayerById(int id)
{
    sqlite3* db;
    sqlite3_open("players.db", &db);

    std::string sql = "SELECT * FROM Player WHERE ID = ?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);

    Player player(0, 0, ""); 
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int playerId = sqlite3_column_int(stmt, 0);
        int team = sqlite3_column_int(stmt, 1);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int points = sqlite3_column_int(stmt, 3);
        int score = sqlite3_column_int(stmt, 4);

        player = Player(playerId, team, name);
        player.setPoints(points);
        player.setScore(score);
    }
    else
    {
        std::cerr << "Jucatorul cu ID-ul " << id << " nu a fost gasit." << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return player;
}
 