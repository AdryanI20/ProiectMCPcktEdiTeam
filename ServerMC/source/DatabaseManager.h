#pragma once
#include <sqlite_orm/sqlite_orm.h>
#include <string>
#include <crow.h>
#include <memory>

namespace sql = sqlite_orm;

struct player {
	int id;
	std::string name;
	int wins;
	int score;
	float fireRate;
};

inline auto createStorage(const std::string& filename)
{
    return sql::make_storage(
        filename,
        sql::make_table(
            "Users",
            sql::make_column("id", &player::id, sql::primary_key().autoincrement()),
            sql::make_column("name", &player::name),
            sql::make_column("wins", &player::wins),
            sql::make_column("score", &player::score),
            sql::make_column("fireRate", &player::fireRate)
        )
    );
}

class DatabaseManager
{
public:
	void CreateDatabase(const std::string& fileName);
	int GetUserIdByUsername(const std::string& username);


private:
    	
    std::shared_ptr<decltype(createStorage(""))> m_storage;
};