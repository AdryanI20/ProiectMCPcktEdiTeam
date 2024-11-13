#pragma once
//#include "Character.h"

class Player
{
public:
	Player() : m_points{ 0 }, m_score{ 0 } {};
	~Player() = default;

	int getPoints();
	void setPoints(int value);
	int getScore();
	void setScore(int value);
private:
	int m_points;
	int m_score;

	int m_id;
	int m_team;

	//Character m_character;
};