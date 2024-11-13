#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include "Weapon.h"

class Character
{
public:
	Character(int id, int team, std::string_view name, std::pair<float, float> startPosition, Weapon weapon)
		: m_id(id), m_team(team), m_name(name), m_startPosition(startPosition), m_playerWeapon(weapon),
		m_health(1), m_lives(3), m_points(0), m_score(0), m_speed(1), m_facingDirection(0), m_position(m_startPosition) {}
	//~Character();

private:
	std::string m_name;
	int m_health;
	int m_lives;
	int m_points;
	int m_score;

	int m_id;
	int m_team;

	float m_speed;
	int m_facingDirection;

	std::pair<float, float> m_startPosition;
	std::pair<float, float> m_position;

	Weapon m_playerWeapon;

public:
	int getFacingDirection();
	void setFacingDirection(int direction);
	int getHealth();
	void setHealth(int value);
	int getLives();
	void setLives(int value);

	int getPoints();
	void setPoints(int value);
	int getScore();
	void setScore(int value);
	std::pair<int, int> getIntPosition();
	void setPosition(std::pair<float, float> position);
	std::pair<float, float> getFloatPosition();
	void setWeapon(float FireRateModifier);
	void fire();
	void update();
	void rotateLeft();
	void rotateRight();
	void move(int direction);

	void eraseBullet(int position);

};