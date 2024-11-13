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
	std::pair<float, float> getFloatPosition();
	void setPosition(int i, int j);
	void setDirection(int direction);
	int getDirection();
	
	void update();
private:
	int m_facingDirection = 0;
	float m_bulletSpeed;
	bool m_isHit;
	std::pair<float, float> m_floatPosition;
	std::pair<int, int>m_position;
};

