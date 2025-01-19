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
    if (m_storage) {
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

    std::cerr << "Database not initialized!" << std::endl;
    return -1;
}

//auto DatabaseManager::GetDatabase(const std::string& fileName)
//{
//	return sqlite_orm::make_storage(
//		fileName,
//		sqlite_orm::make_table(
//			"Players",
//			sqlite_orm::make_column("id", &player::id, sqlite_orm::primary_key().autoincrement()),
//			sqlite_orm::make_column("name", &player::name),
//			sqlite_orm::make_column("points", &player::points),
//			sqlite_orm::make_column("score", &player::score),
//			sqlite_orm::make_column("fire_rate", &player::fireRate),
//			sqlite_orm::make_column("speed", &player::speed),
//			sqlite_orm::make_column("scoreReached", &player::scoreReached)
//		)
//	);
//}
//
//void DatabaseManager::AddPlayer(const std::string& fileName,
//	int id, std::string name, int points, int score, float fireRate, float speed)
//{
//	auto storage = GetDatabase(fileName);
//	player newPlayer{ 0, name, points, score, fireRate, speed };
//	storage.insert(newPlayer);
//}
//
//player DatabaseManager::GetPlayer(const std::string& fileName, int id)
//{
//	auto storage = GetDatabase(fileName);
//	player foundPlayer = storage.get<player>(id);
//	return foundPlayer;
//}
//
//player DatabaseManager::GetPlayer(const std::string& fileName, std::string name)
//{
//	auto storage = GetDatabase(fileName);
//	auto foundPlayers = storage.get_all<player>(sqlite_orm::where(sqlite_orm::c(&player::name) == name));
//	return foundPlayers[0];
//}
//
//int DatabaseManager::GetPlayerID(const std::string& fileName, std::string nume)
//{
//	auto storage = GetDatabase(fileName);
//	player foundPlayer = storage.get<player>(nume);
//	return foundPlayer.id;
//}
//
//int DatabaseManager::GetPlayerScore(const std::string& fileName, int id)
//{
//	auto storage = GetDatabase(fileName);
//	player foundPlayer = storage.get<player>(id);
//	return foundPlayer.score;
//}
//
//void DatabaseManager::SetPlayerScore(const std::string& fileName, int id, int score)
//{
//	auto storage = GetDatabase(fileName);
//	auto playerData = storage.get_pointer<player>(id);
//	playerData->score = score;
//	storage.update(*playerData);
//}
//
//int DatabaseManager::GetPlayerPoints(const std::string& fileName, int id)
//{
//	auto storage = GetDatabase(fileName);
//	player foundPlayer = storage.get<player>(id);
//	return foundPlayer.points;
//}
//
//void DatabaseManager::SetPlayerPoints(const std::string& fileName, int id, int points)
//{
//	auto storage = GetDatabase(fileName);
//	auto playerData = storage.get_pointer<player>(id);
//	playerData->points = points;
//	storage.update(*playerData);
//}
//
//int DatabaseManager::GetFireRate(const std::string& fileName, int id)
//{
//	auto storage = GetDatabase(fileName);
//	player foundPlayer = storage.get<player>(id);
//	return foundPlayer.fireRate;
//}
//
//void DatabaseManager::SetFireRate(const std::string& fileName, int id, float fireRate)
//{
//	auto storage = GetDatabase(fileName);
//	auto playerData = storage.get_pointer<player>(id);
//	playerData->fireRate = fireRate;
//	storage.update(*playerData);
//}
//
//bool DatabaseManager::GetScoreReachedState(const std::string& fileName, int id)
//{
//	auto storage = GetDatabase(fileName);
//	player foundPlayer = storage.get<player>(id);
//	return foundPlayer.scoreReached;
//}
//
//void DatabaseManager::SetScoreReachedState(const std::string& fileName, int id, bool state)
//{
//	auto storage = GetDatabase(fileName);
//	auto playerData = storage.get_pointer<player>(id);
//	playerData->scoreReached = state;
//	storage.update(*playerData);
//}
//
//void DatabaseManager::ShowDatabase(const std::string& fileName)
//{
//	auto storage = GetDatabase(fileName);
//	auto allPlayers = storage.get_all<player>();
//
//	if (allPlayers.empty())
//	{
//		std::cout << "Database is empty." << std::endl;
//		return;
//	}
//
//	std::cout << "ID | Name       | Points | Score | FireRate | Speed | ScoreReached" << std::endl;
//	std::cout << "---------------------------------------------------------------" << std::endl;
//
//	for (const auto& player : allPlayers)
//	{
//		std::cout << player.id << " | "
//			<< player.name << " | "
//			<< player.points << " | "
//			<< player.score << " | "
//			<< player.fireRate << " | "
//			<< player.speed << " | "
//			<< (player.scoreReached ? "Yes" : "No") << std::endl;
//	}
//}
//
//void DatabaseManager::UpgradeFireRate(const std::string& fileName, int id)
//{
//	auto storage = GetDatabase(fileName);
//	auto playerData = storage.get_pointer < player>(id);
//	if (playerData->fireRate < 4 && playerData->points >= 500)
//	{
//		playerData->points -= 500;
//		playerData->fireRate += 1;
//	}
//}