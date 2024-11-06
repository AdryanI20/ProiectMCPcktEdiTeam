#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include "Bullet.h"

class Weapon
{
public:
	Weapon() : m_damage(1), m_fireRate(0.25), m_isBulletFired(false) {}
	~Weapon(){}

    void setWeaponStats(float fireRate);
	int getDamage();
	float getfireRate();
	void isBulletFired(bool isFired); 
	void shoot(int direction);
	void bulletPush(Bullet b);
	void setPosition(int i, int j);
	
private:
	std::vector<Bullet> bullets_shot;
	int m_damage;
	float m_fireRate;
	bool m_isBulletFired;
	std::pair<int, int> m_position;
};
