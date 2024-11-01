#pragma once
class Bullet
{
public:
	Bullet():m_bulletSpeed(0.25){}
	~Bullet(){}

	void isHit(bool hit);
	void updateSpeed();
	std::pair<int, int> getPosition();
	void setPosition(int i, int j);
private:
	float m_bulletSpeed;
	bool m_isHit;
	std::pair<int, int>m_position;
};

