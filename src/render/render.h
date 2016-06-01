#pragma once

#include <cstdint>
#include "vector.h"
#include <memory>
#include <string>

namespace render
{
    class SpriteSheet;
    int32_t LoadSpriteSheet(const std::string& filename, const std::string& name);
    std::shared_ptr<SpriteSheet> GetSpriteSheet(int32_t id);
    std::shared_ptr<SpriteSheet> GetSpriteSheet(const std::string& name);
    
    struct DrawOperation
    {
        int32_t surface;
        Vector2 from_position;
        Vector2 to_position;
        Vector2 size;
    };
}