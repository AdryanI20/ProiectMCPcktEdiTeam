#include "Bullet.h"

void Bullet::isHit(bool hit)
{
	m_isHit = hit;
}

void Bullet::updateSpeed()
{
	m_bulletSpeed = m_bulletSpeed * 2;
}

std::pair<int, int> Bullet::getPosition()
{
	return m_position;
}

std::pair<float, float> Bullet::getFloatPosition()
{
	return m_floatPosition;
}

void Bullet::setPosition(int i, int j)
{
	m_position.first = i;
	m_position.second = j;

	m_floatPosition = m_position;
}

void Bullet::setDirection(int direction)
{
	m_facingDirection = direction;
}

int Bullet::getDirection()
{
	return m_facingDirection;
}

void Bullet::update()
{
	if (m_facingDirection == 0)
	{
		m_floatPosition.first = m_floatPosition.first - m_bulletSpeed;
		m_position.first =static_cast<int>(m_floatPosition.first);
	}
	if (m_facingDirection == 1)
	{
		m_floatPosition.second = m_floatPosition.second + m_bulletSpeed;
		m_position.second = static_cast<int>(m_floatPosition.second);
	}
	if (m_facingDirection == 2)
	{
		m_floatPosition.first = m_floatPosition.first + m_bulletSpeed;
		m_position.first = static_cast<int>(m_floatPosition.first);
	}
	if (m_facingDirection == 3)
	{
		m_floatPosition.second = m_floatPosition.second - m_bulletSpeed;
		m_position.second = static_cast<int>(m_floatPosition.second);
	}
}
