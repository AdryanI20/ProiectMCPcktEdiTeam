#pragma once
#include <string>

class Player
{
public:
	Player(int id, int team, std::string name);
	~Player();

	int getId();
	void setTeam(int team);
	int getTeam();
	int getPoints();
	void setPoints(int value);
	int getScore();
	void setScore(int value);
	void setName(std::string name);
	std::string getName();

	bool hasSpecialBullet() const { return m_hasSpecialBullet; }
	void useSpecialBullet() { m_hasSpecialBullet = false; } // Consumă glonțul special


private:
	int m_id;
	int m_team;
	int m_points;
	int m_score;
	std::string m_name;

	bool m_hasSpecialBullet = false; // Indică dacă jucătorul are glonțul special
};