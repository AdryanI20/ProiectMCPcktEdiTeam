#include "DatabaseManager.h"

void DatabaseManager::CreateDatabase(const std::string& fileName)
{
    m_storage = std::make_shared<decltype(createStorage(""))>(sql::make_storage(
            fileName,
            sql::make_table(
                "Users",
                sql::make_column("id", &player::id, sql::primary_key().autoincrement()),
                sql::make_column("name", &player::name),
                sql::make_column("wins", &player::wins),
                sql::make_column("score", &player::score),
                sql::make_column("fireRate", &player::fireRate)
            )
        )
    );

    m_storage->sync_schema();
}

int DatabaseManager::GetUserIdByUsername(const std::string& username) {
    if (!m_storage) {
        std::cerr << "Database not initialized!" << std::endl;
        return -1;
    }

    auto userCount = m_storage->get_all<player>();
    auto userSearch = m_storage->select(
        sql::columns(&player::id),
        sql::where(sql::is_equal(&player::name, username))
    );

    if (!userSearch.empty()) {
        return std::get<0>(userSearch.front());
    }
    else {
        m_storage->insert(
            sql::into<player>(),
            sql::columns(
                &player::name,
                &player::wins,
                &player::score,
                &player::fireRate
            ),
            sql::values(
                std::make_tuple(
                    username,
                    0,
                    0,
                    0.0
                )
            )
        );
        return userCount.size()+1;
    }   
}

void DatabaseManager::SetUserFirerate(int clientID, float fireRate) {
    m_storage->update_all(
        sql::set(sql::c(&player::fireRate) = fireRate),
        sql::where(sql::c(&player::id) == clientID)
    );
}

float DatabaseManager::GetUserFirerate(int clientID) {
    auto userSearch = m_storage->select(
        sql::columns(&player::fireRate),
        sql::where(sql::is_equal(&player::id, clientID))
    );
    if (!userSearch.empty()) {
        return std::get<0>(userSearch.front());
    }
}

void DatabaseManager::SetUserScore(int clientID, int score) {
    m_storage->update_all(
        sql::set(sql::c(&player::score) = score),
        sql::where(sql::c(&player::id) == clientID)
    );
}

int DatabaseManager::GetUserScore(int clientID) {
    auto userSearch = m_storage->select(
        sql::columns(&player::score),
        sql::where(sql::is_equal(&player::id, clientID))
    );
    if (!userSearch.empty()) {
        return std::get<0>(userSearch.front());
    }
}

void DatabaseManager::SetUserWins(int clientID, int wins) {
    m_storage->update_all(
        sql::set(sql::c(&player::wins) = wins),
        sql::where(sql::c(&player::id) == clientID)
    );
}

int DatabaseManager::GetUserWins(int clientID) {
    auto userSearch = m_storage->select(
        sql::columns(&player::wins),
        sql::where(sql::is_equal(&player::id, clientID))
    );
    if (!userSearch.empty()) {
        return std::get<0>(userSearch.front());
    }
}