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
	void shoot(int direction, int pozitie_actuala_i, int pozitie_actuala_j);

	
private:
	std::vector<Bullet> bullets_shot;
	int m_damage;
	float m_fireRate;
	bool m_isBulletFired;
};
