#pragma once
#include <utility>
class Bullet
{
public:
	Bullet():m_bulletSpeed(0.25), m_isHit(false){}
	~Bullet(){}

	void isHit(bool hit);
	void updateSpeed();
	std::pair<int, int> getPosition();
	void setPosition(int i, int j);
	void setDirection(int direction);
	void update();
private:
	int m_facingDirection = 0;
	float m_bulletSpeed;
	bool m_isHit;
	std::pair<int, int>m_position;
};

