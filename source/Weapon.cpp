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

void Weapon::setWeaponStats(float fireRateModifier)
{
	m_fireRate = m_fireRate*fireRateModifier;
}

void Weapon::bulletPush(Bullet b)
{
	m_bullets.push_back(b);
}

std::vector<Bullet> Weapon::getBulletsVector()
{
	return m_bullets;
}

void Weapon::setPosition(int i, int j)
{
	m_position.first = i;
	m_position.second = j;
}

void Weapon::setBulletSpeed()
{
	m_speed *= 2;
}

void Weapon::shoot(int direction)
{
	Bullet newBullet(m_speed);
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

void Weapon::deleteBullet(int position)
{
	m_bullets.erase(m_bullets.begin()+position-1);
}


