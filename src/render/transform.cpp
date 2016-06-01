#include "transform.h"

Transform::Transform()
    : position_(0.f, 0.f)
    , rotation_(0.f)
{
}

void Transform::Translate(const Vector2& offset)
{
    position_ += offset;
}

void Transform::SetPosition(const Vector2& position)
{
    position_ = position;
}

Vector2 Transform::GetPosition() const
{
    return position_;
}

void Transform::Rotate(const float& degrees)
{
    rotation_ += degrees;
}

void Transform::SetRotation(const float& degrees)
{
    rotation_ = degrees;
}

float Transform::GetRotation() const
{
    return rotation_;
}