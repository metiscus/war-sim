#include "camera.h"

namespace render
{
    Camera::Camera()
    {
        
    }
    
    void Camera::Translate(const Vector2& center)
    {
        center_ += center;
    }
    
    void Camera::SetCenter(const Vector2& center)
    {
        center_ = center;
    }
    
    void Camera::SetWidth(float width)
    {
        extents_.x = width;
    }
    
    void Camera::SetHeight(float height)
    {
        extents_.y = height;
    }
    
    Vector2 Camera::GetCenter() const
    {
        return center_;
    }
    
    float Camera::GetHeight() const
    {
        return extents_.y;
    }
    
    float Camera::GetWidth() const
    {
        return extents_.x;
    }
    
}