#pragma once
#include <utility>
class Bullet
{
public:
	Bullet(float bulletSpeed):m_speed(bulletSpeed), m_isHit(false){}
	~Bullet(){}

	void isHit(bool hit);
	std::pair<int, int> getPosition();
	std::pair<float, float> getFloatPosition();
	void setPosition(int i, int j);
	void setDirection(int direction);
	int getDirection();
	
	void update();
private:
	int m_facingDirection = 0;
	float m_speed;
	bool m_isHit;
	std::pair<float, float> m_floatPosition;
	std::pair<int, int>m_position;
};

