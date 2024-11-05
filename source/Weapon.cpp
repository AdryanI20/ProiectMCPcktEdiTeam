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


