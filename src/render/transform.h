#pragma once

#include "vector.h"

namespace render
{
class Transform
{
private:
    Vector2 position_;
    float rotation_;
    
public:
    Transform();
    
    void Translate(const Vector2& offset);
    void SetPosition(const Vector2& position);
    Vector2 GetPosition() const;
    
    void Rotate(const float& degrees);
    void SetRotation(const float& degrees);
    float GetRotation() const;
};
}