#pragma once

namespace render
{

typedef struct Vector2
{
    float x;
    float y;
    
    Vector2(float x_ = 0.f, float y_ = 0.f);
    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    Vector2 operator*(const float& rhs) const;
    Vector2 operator/(const float& rhs) const;
    
    Vector2& operator=(const Vector2& rhs);
    
    Vector2& operator+=(const Vector2& rhs);
    Vector2& operator-=(const Vector2& rhs);
    Vector2& operator*=(const float& rhs);
    Vector2& operator/=(const float& rhs);
    
    float Magnitude() const;
    Vector2 AsUnit() const;
} Vector2;

Vector2 operator*(const float& lhs, const Vector2& rhs);

}