#pragma once

#include <sqlite_orm/sqlite_orm.h>
#include <string>
#include <crow.h>

namespace sql = sqlite_orm;

struct player
{
	int id;
	std::string name;
	int points;
	int score;
	float fireRate;
	float speed;
	bool scoreReached;
};

class DatabaseManager
{
public:
	void CreateDatabase(const std::string& fileName);

	auto GetDatabase(const std::string& fileName);

	void AddPlayer(const std::string& fileName,
		int id, std::string name = "Name", int points = 0, int score = 0, float fireRate = 1, float speed = 1);

	player GetPlayer(const std::string& fileName, int id);
	player GetPlayer(const std::string& fileName, std::string name);

	int GetPlayerID(const std::string& fileName, std::string name);

	int GetPlayerScore(const std::string& fileName, int id);
	void SetPlayerScore(const std::string& fileName, int id, int score);

	bool GetScoreReachedState(const std::string& fileName, int id);
	bool SetScoreReachedState(const std::string& fileName, int id, bool state);

	int GetPlayerPoints(const std::string& fileName, int id);
	void SetPlayerPoints(const std::string& fileName, int id, int points);

	int GetFireRate(const std::string& fileName, int id);
	void SetFireRate(const std::string& fileName, int id, float fireRate);
};