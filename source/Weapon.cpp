#include "Weapon.h"

int Weapon::getDamage()
{
	return m_damage;
}

float Weapon::getfireRate()
{
	return m_fireRate;
}

void Weapon::isBulletFired(bool isFired)
{
	m_isBulletFired = isFired;
}

void Weapon::setWeaponStats(float fireRate)
{
	m_fireRate = fireRate;
}

void Weapon::bulletPush(Bullet b)
{
	bullets_shot.push_back(b);
}

void Weapon::setPosition(int i, int j)
{
	m_position.first = i;
	m_position.second = j;
}

void Weapon::shoot(int direction)
{
	Bullet newBullet;
	newBullet.setDirection(direction);
	if (direction == 0)
	{
		newBullet.setPosition(m_position.first-1, m_position.second);
	}
	if (direction == 1)
	{
		newBullet.setPosition(m_position.first, m_position.second+1);
	}
	if (direction == 2)
	{
		newBullet.setPosition(m_position.first+1, m_position.second);
	}
	if (direction == 3)
	{
		newBullet.setPosition(m_position.first, m_position.second -1);
	}

	this->bulletPush(newBullet);
}


