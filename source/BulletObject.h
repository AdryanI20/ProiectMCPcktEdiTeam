#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:
    Bullet(int X, int Y, float speed, int direction);

    void Update(Game* game) override;
    void Clean() override;

    void setDirection(int direction);
    int getDirection() const;

    Vector2D getPosition() const;
    void setPosition(int X, int Y);

    bool isHit() const;
    void setHit(bool hitStatus);

private:
    float m_speed; 
    int m_facingDirection; 
    bool m_isHit;          
};


