#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include "BulletObject.h"
#include <vector>

class Character
{
public:
	Character(std::pair<float, float> startPosition)
		: m_startPosition(startPosition), m_lives(3), m_points(0), m_score(0), 
		  m_speed(1), m_facingDirection(0), m_position(m_startPosition) {}
	//~Character();

	int getFacingDirection();
	void setFacingDirection(int direction);
	int getLives();
	void setLives(int value);
	void aliveOrDead(bool lifeState);

	std::pair<int, int> getIntPosition();
	void setPosition(std::pair<float, float> position);
	std::pair<float, float> getFloatPosition();
	void update();
	void move(int direction);
	void rotateLeft();
	void rotateRight();
	void respawn(float row, float col);
	void dead();

private:

	int m_lives;
	int m_points;
	int m_score;
	bool m_isAlive;

	float m_speed;
	int m_facingDirection;

	std::pair<float, float> m_startPosition;
	std::pair<float, float> m_position;

    int m_row;
    int m_col;
};