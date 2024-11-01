#include "Bullet.h"

Bullet::isHit(bool hit)
{
	m_isHit = hit;
}

Bullet::updateSpeed()
{
	m_bulletSpeed = m_bulletSpeed * 2;
}

Bullet::getPosition()
{
	return m_position;
}

Bullet::setPosition(int i, int j)
{
	m_position.first = i;
	m_position.second = j;
}