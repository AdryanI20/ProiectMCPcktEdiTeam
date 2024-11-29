#include "BulletObject.h"

Bullet::Bullet(int X, int Y, float speed, int direction)
    : GameObject(X, Y), m_speed(speed), m_facingDirection(direction), m_isHit(false) {}

void Bullet::Update(Game* game) {
    //if (!m_isHit) {
    //    switch (m_facingDirection) {
    //    case 0:
    //        m_pos.setX(m_pos.getX() - m_speed);
    //        break;
    //    case 1:
    //        m_pos.setY(m_pos.getY() + m_speed);
    //        break;
    //    case 2:
    //        m_pos.setX(m_pos.getX() + m_speed);
    //        break;
    //    case 3:
    //        m_pos.setY(m_pos.getY() - m_speed);
    //        break;
    //    default:
    //        break;
    //    }
    //}
}

void Bullet::Clean() {
}

void Bullet::setDirection(int direction) {
    m_facingDirection = direction;
}

int Bullet::getDirection() const {
    return m_facingDirection;
}

Vector2D Bullet::getPosition() const {
    return m_pos;
}

void Bullet::setPosition(int X, int Y) {
    m_pos.setX(X);
    m_pos.setY(Y);
}

bool Bullet::isHit() const {
    return m_isHit;
}

void Bullet::setHit(bool hitStatus) {
    m_isHit = hitStatus;
}
