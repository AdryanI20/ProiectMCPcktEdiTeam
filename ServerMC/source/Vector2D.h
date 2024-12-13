#pragma once
#include <math.h>

class Vector2D
{
public:
    Vector2D(float X, float Y);

    float getX() const;
    float getY() const;

    void setX(float X);
    void setY(float Y);

    float length();

    Vector2D operator+(const Vector2D& v2) const;
    Vector2D operator*(float scalar);
    Vector2D operator-(const Vector2D& v2) const;
    Vector2D operator/(float scalar);

    bool operator==(const Vector2D& v2) const;

    Vector2D& operator/=(float scalar);
    Vector2D& operator*=(float scalar);
    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);

    void normalise();
private:

    float m_x, m_y;
};