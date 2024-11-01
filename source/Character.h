#pragma once
#include <cstdint>
#include <string>
#include <string_view>

// #include "Weapon.h"

class Character
{
public:
	Character(int id, int team, std::string_view name, int points, int score, std::pair<int, int> startPosition);
	~Character();
private:
	const std::string m_name;
	int m_health{ 1 };
	int m_lives{ 3 };
	int m_points;
	int m_score;

	int m_id;
	int m_team;

	const float m_speed{ 1 };
	int m_facingDirection{ 0 };

	const std::pair<int, int> m_startPosition;
	std::pair<int, int> m_position{ m_startPosition };

	//Weapon playerWeapon;

public:
	void rotateLeft();
	void rotateRight();
	int getFacingDirection();
	void setFacingDirection(int direction);
	void move(int direction);
	int getHealth();
	void setHealth(int value);
	int getPoints();
	void setPoints(int value);
	int getScore();
	void setScore(int value);
	std::pair<int, int> getPosition();
	void setPosition(std::pair<int, int> position);
};