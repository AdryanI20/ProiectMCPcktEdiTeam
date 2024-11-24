#include "Player.h"
#include "Character.h"

Player::~Player()
{
	removeCharacter();
}

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

void Player::removeCharacter()
{
	delete m_character;
	m_character = nullptr;
}

void Player::setCharacter(Character* character)
{
	removeCharacter();
	m_character = character;
}

void Player::checkCharacter()
{
	if (m_character->getLives() == 0)
	{
		removeCharacter();
		setTeam(-1);
	}
}

void Player::setName(std::string name)
{
	m_name = name;
}

std::string Player::getName()
{
	return m_name;
}