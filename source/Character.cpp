#include "Character.h"
#include <string_view>
#include <ctime>

int Character::getFacingDirection()
{
	return m_facingDirection;
}

void Character::setFacingDirection(int direction)
{
	m_facingDirection = direction;
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

void Character::move(int direction)
{
	switch (direction)
	{
	case 0:
		m_position.first -= m_speed;
		break;
	case 1:
		m_position.second += m_speed;
		break;
	case 2:
		m_position.first += m_speed;
		break;
	case 3:
		m_position.second -= m_speed;
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

std::pair<float, float> Character::getFloatPosition()
{
	return m_position;
}

std::pair<int, int> Character::getIntPosition()
{
	return std::make_pair(static_cast<int>(m_position.first), static_cast<int>(m_position.second));
}

void Character::setPosition(std::pair<float, float> position)
{
	m_position = position;
}

void Character::setWeapon(float FireRateModifier)
{
	m_playerWeapon.setWeaponStats(FireRateModifier);
}

void Character::fire()
{
	m_playerWeapon.shoot(m_facingDirection);
}

void Character::update()
{
	move(getFacingDirection());
}