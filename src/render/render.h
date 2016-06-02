#pragma once

#include <cstdint>
#include "vector.h"
#include <memory>
#include <string>
#include <vector>

namespace render
{
    class SpriteSheet;
    int32_t LoadSpriteSheet(const std::string& filename, const std::string& name);
    std::shared_ptr<SpriteSheet> GetSpriteSheet(int32_t id);
    std::shared_ptr<SpriteSheet> GetSpriteSheet(const std::string& name);
    
    class Canvas;
    
    struct DrawOperation
    {
        int32_t surface;
        Vector2 from_position;
        Vector2 from_size;
        Vector2 to_position;
        Vector2 to_size;
    };
    
    void CreateWindow(const char* title, uint32_t width, uint32_t height);
    void ClearWindow();
    void DrawWindow(const std::vector<DrawOperation>& operations);
    void PresentWindow();
}