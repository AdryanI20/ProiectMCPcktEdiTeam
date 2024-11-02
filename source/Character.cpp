#include "Character.h"
#include <string_view>

Character::Character(int id, int team, std::string_view name, std::pair<int, int> startPosition)
{
	m_id = id;
	m_team = team;
	m_name = name;
	m_startPosition = startPosition;
}

Character::~Character()
{

}

void Character::rotateLeft()
{
	m_facingDirection--;

	if (m_facingDirection == -1)
		m_facingDirection = 3;
}

void Character::rotateRight()
{
	m_facingDirection++;
	
	if (m_facingDirection == 4)
		m_facingDirection = 0;
}

int Character::getFacingDirection()
{
	return m_facingDirection;
}

void Character::setFacingDirection(int direction)
{
	m_facingDirection = direction;
}

void Character::move(int direcction)
{
	switch (direcction)
	{
	case 0:
		m_position.first--;
		break;
	case 1:
		m_position.second--;
		break;
	case 2:
		m_position.first++;
		break;
	case 3:
		m_position.second++;
		break;
	default:
		break;
	}
}

int Character::getHealth()
{
	return m_health;
}

void Character::setHealth(int value)
{
	m_health = value;
}

int Character::getLives()
{
	return m_lives;
}

void Character::setLives(int value)
{
	m_lives = value;
}

int Character::getPoints()
{
	return m_points;
}

void Character::setPoints(int value)
{
	m_points = value;
}

int Character::getScore()
{
	return m_score;
}

void Character::setScore(int value)
{
	m_score = value;
}

std::pair<int, int> Character::getPosition()
{
	return m_position;
}

void Character::setPosition(std::pair<int, int> position)
{
	m_position = position;
}

void Character::setWeapon(Weapon weapon)
{
	m_playerWeapon = weapon;
}