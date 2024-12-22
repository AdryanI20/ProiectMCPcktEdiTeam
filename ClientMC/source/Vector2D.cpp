#include "Vector2D.h"

Vector2D::Vector2D(float X, float Y) : m_x(X), m_y(Y) {}

float Vector2D::getX() const {
	return m_x; 
}
float Vector2D::getY() const {
	return m_y; 
}

void Vector2D::setX(float X) { 
    m_x = X;
}
void Vector2D::setY(float Y) { 
    m_y = Y;
}

float Vector2D::length() {
    return sqrt(m_x * m_x + m_y * m_y);
}

Vector2D Vector2D::operator+(const Vector2D& v2) const {
    return Vector2D(m_x + v2.getX(), m_y + v2.getY());
}

Vector2D Vector2D::operator*(float scalar) {
    return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D& Vector2D::operator*=(float scalar) {
    m_x *= scalar;
    m_y *= scalar;

    return *this;
}

Vector2D Vector2D::operator-(const Vector2D& v2) const {
    return Vector2D(m_x - v2.getX(), m_y - v2.getY());
}

Vector2D Vector2D::operator/(float scalar) {
    return Vector2D(m_x / scalar, m_y / scalar);
}

bool Vector2D::operator==(const Vector2D& v2) const
{
    return m_x == v2.getX() && m_y == v2.getY();
}

Vector2D& Vector2D::operator/=(float scalar) {
    m_x /= scalar;
    m_y /= scalar;

    return *this;
}

Vector2D& operator+=(Vector2D& v1, const Vector2D& v2) {
    v1.m_x += v2.getX();
    v1.m_y += v2.getY();

    return v1;
}

Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
{
    v1.m_x -= v2.getX();
    v1.m_y -= v2.getY();

    return v1;
}

void Vector2D::normalise() {
    float l = length();
    if (l > 0)
    {
        (*this) *= 1 / 1;
    }
}
