#pragma once
#include <string>
#include <cstdint>
#include "Bullet.h"

class Weapon
{
public:
	Weapon() : m_damage(1), m_fireRate(0.25), m_isBulletFired(false) {}
	~Weapon(){}

    void setWeaponStats(float fireRate);
	int getDamage();
	int getfireRate();
	void isBulletFired(bool isFired); 
	void shoot(int direction);

private:
	int m_damage;
	float m_fireRate;
	bool m_isBulletFired;
};
