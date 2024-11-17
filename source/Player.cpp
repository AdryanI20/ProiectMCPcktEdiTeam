#include "Player.h"
#include "Character.h"

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