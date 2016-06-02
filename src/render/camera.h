#pragma once

#include "vector.h"

namespace render
{
   
    class Camera
    {
    private:
        Vector2 center_;
        Vector2 extents_;
    public:
        Camera();
        void Translate(const Vector2& center);
        void SetCenter(const Vector2& center);
        void SetWidth(float width);
        void SetHeight(float height);
        Vector2 GetCenter() const;
        float GetHeight() const;
        float GetWidth() const;
    };
}