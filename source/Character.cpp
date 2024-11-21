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

int Character::getLives()
{
	return m_lives;
}

void Character::setLives(int value)
{
	m_lives = value;
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

void Character::aliveOrDead(bool lifeState)
{
	m_isAlive = lifeState;
}

void Character::dead()
{
	for (int i = 0; i < m_playerWeapon.getBulletsVector().size(); i++)
	{
		m_playerWeapon.getBulletsVector().erase(m_playerWeapon.getBulletsVector().begin()+i);
	}
	this->aliveOrDead(false);
	m_lives--;
}

void Character::respawn(float row, float col)
{
	if (m_lives == 0)
		return;
	m_position.first = row;
	m_position.second = col;
	this->aliveOrDead(true);
}

std::vector<Bullet> Character::getPlayerBullets()
{
	return m_playerWeapon.getBulletsVector();
}