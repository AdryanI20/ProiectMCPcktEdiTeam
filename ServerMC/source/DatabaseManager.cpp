#include "DatabaseManager.h"

#include <sqlite_orm/sqlite_orm.h>

struct player
{
	int id;
	std::string name;
	int points;
	int score;
	float fireRate;
	float speed;
};

auto DatabaseManager::CreateDatabase(const std::string& fileName)
{
	auto storage = sql::make_storage(
		fileName,
		sql::make_table(
			"Players",
			sql::make_column("id", &player::id, sql::primary_key().autoincrement()),
			sql::make_column("name", &player::name),
			sql::make_column("points", &player::points),
			sql::make_column("score", &player::score),
			sql::make_column("fireRate", &player::fireRate),
			sql::make_column("speed", &player::speed)
		)
	);

	storage.sync_schema();
	
	return storage;
}

auto GetDatabase(const std::string& DBname)
{
	return sqlite_orm::make_storage(
		DBname,
		sqlite_orm::make_table(
			"Players",
			sqlite_orm::make_column("id", &player::id, sqlite_orm::primary_key().autoincrement()),
			sqlite_orm::make_column("name", &player::name),
			sqlite_orm::make_column("points", &player::points),
			sqlite_orm::make_column("score", &player::score),
			sqlite_orm::make_column("fire_rate", &player::fireRate),
			sqlite_orm::make_column("speed", &player::speed)
		)
	);
}

