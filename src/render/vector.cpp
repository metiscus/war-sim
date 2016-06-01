#include "vector.h"
#include <cfloat>
#include <cmath>

namespace render 
{

Vector2::Vector2(float x_, float y_)
    : x(x_)
    , y(y_)
{
    
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
    return Vector2(x+rhs.x, y+rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
    return Vector2(x-rhs.x, y-rhs.y);
}

Vector2 Vector2::operator*(const float& rhs) const
{
    return Vector2(x*rhs, y*rhs);
}

Vector2 Vector2::operator/(const float& rhs) const
{
    float inv = 1.0f / (rhs + FLT_EPSILON);
    return Vector2(x * inv, y * inv);
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vector2& Vector2::operator*=(const float& rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
}

Vector2& Vector2::operator/=(const float& rhs)
{
    float inv = 1.0f / (rhs + FLT_EPSILON);
    x *= inv;
    y *= inv;
    return *this;
}

float Vector2::Magnitude() const
{
    return sqrtf(x*x+y*y);
}

Vector2 Vector2::AsUnit() const
{
    float invMag = 1.0f / (Magnitude() + FLT_EPSILON);
    return Vector2(x*invMag, y*invMag);
}

Vector2 operator*(const float& lhs, const Vector2& rhs)
{
    return Vector2(lhs*rhs.x, lhs*rhs.y);
}
}