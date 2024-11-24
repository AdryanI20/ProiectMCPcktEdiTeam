#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include "Bullet.h"

class Weapon
{
public:
	Weapon() : m_damage(1), m_fireRate(0.25), m_isBulletFired(false), m_speed(0.25) {}
	~Weapon(){}

    void setWeaponStats(float fireRateModifier);
	int getDamage();
	float getfireRate();
	std::vector<Bullet*>& getBulletsVector();
	void isBulletFired(bool isFired); 
	void shoot(int direction);
	void bulletPush(Bullet* b);
	void setPosition(int i, int j);
	void setBulletSpeed();
	void deleteBullet(int position);
	void deleteAllBullets();
	
private:
	std::vector<Bullet*> m_bullets;
	int m_damage;
	float m_fireRate;
	bool m_isBulletFired;
	float m_speed;
	std::pair<int, int> m_position;
};
