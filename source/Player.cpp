#include "Player.h"
#include "Character.h"

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

void Player::setCharacter(Character* character)
{
	m_character = character;
}

void Player::setName(std::string name)
{
	m_name = name;
}

std::string Player::getName()
{
	return m_name;
}