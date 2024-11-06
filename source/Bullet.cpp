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

void Bullet::setPosition(int i, int j)
{
	m_position.first = i;
	m_position.second = j;
}

void Bullet::setDirection(int direction)
{
	m_facingDirection = direction;
}

void Bullet::update()
{
	if (m_facingDirection == 0)
	{
		float poz = m_position.first - m_bulletSpeed;
		m_position.first =static_cast<int>(poz);
	}
	if (m_facingDirection == 1)
	{
		float poz = m_position.second + m_bulletSpeed;
		m_position.second = static_cast<int>(poz);
	}
	if (m_facingDirection == 2)
	{
		float poz = m_position.first + m_bulletSpeed;
		m_position.first = static_cast<int>(poz);
	}
	if (m_facingDirection == 3)
	{
		float poz = m_position.second - m_bulletSpeed;
		m_position.second = static_cast<int>(poz);
	}
}
