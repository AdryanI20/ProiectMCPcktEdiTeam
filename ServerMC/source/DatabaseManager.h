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
};

class DatabaseManager
{
public:
	auto CreateDatabase(const std::string& DBname);

	auto GetDatabase(const std::string& DBname);

	void AddPlayer(const std::string& DBname, 
		int id, std::string name = "Name", int points = 0, int score = 0, float fireRate = 1, float speed = 1);

	player GetPlayer(const std::string& DBname, int id);
	player GetPlayer(const std::string& DBname, std::string name);

	int GetPlayerID(const std::string& DBname, std::string name);

	int GetPlayerPoints(const std::string& DBname, std::string name);

	void PlayerUsePoints(const std::string& DBname, int points);

	int GetFireRate(const std::string& DBname, std::string name);

	int GetPlayerScore(const std::string& DBname, std::string name);

	void AddPoints(const std::string& filename, std::string name, int points);

	void AddScore(const std::string& filename, std::string name, int score);

	void UpdateFireRate(const std::string& filename, std::string name, float fireRate);
};