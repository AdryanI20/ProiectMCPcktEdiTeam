#pragma once
//#include "Character.h"

class Player
{
public:
	Player(int id, int team) : m_id{ id }, m_team{ team }, m_points { 0 }, m_score{ 0 } {};
	~Player() = default;

	int getPoints();
	void setPoints(int value);
	int getScore();
	void setScore(int value);
private:
	int m_id;
	int m_team;

	int m_points;
	int m_score;

	//Character m_character;
};