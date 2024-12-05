#include "Player.h"

Player::Player(int id, int team, std::string name) : m_id{ id }, m_team{ team }
, m_name{ name }, m_points{ 0 }, m_score{ 0 } {}

Player::~Player() {}

int Player::getId()
{
	return m_id;
}

void Player::setTeam(int team)
{
	m_team = team;
}

int Player::getTeam()
{
	return m_team;
}

int Player::getPoints()
{
	return m_points;
}

void Player::setPoints(int value)
{
	m_points = value;
}

int Player::getScore()
{
	return m_score;
}

void Player::setScore(int value)
{
	m_score = value;
}

void Player::setName(std::string name)
{
	m_name = name;
}

std::string Player::getName()
{
	return m_name;
}

