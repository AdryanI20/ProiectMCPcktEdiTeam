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