#pragma once
#include <string>

#include "Character.h"

class Player
{
public:
	Player(int id, int team, Character* character, std::string name) : m_id{ id }, m_team{ team }
		, m_character{ character }, m_name{ name }, m_points { 0 }, m_score{ 0 } {};
	~Player() = default;

	int getId();
	void setTeam(int team);
	int getTeam();
	int getPoints();
	void setPoints(int value);
	int getScore();
	void setScore(int value);
	void setCharacter(Character* character);
	void setName(std::string name);
	std::string getName();

private:
	int m_id;
	int m_team;
	int m_points;
	int m_score;
	std::string m_name;

	Character* m_character;
};