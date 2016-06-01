#pragma once

#include "node.h"
#include "spritesheet.h"
#include <memory>

namespace render
{

class Sprite : public Node
{
    std::shared_ptr<SpriteRegion> region_;

public:    
    void SetSpriteRegion(const std::shared_ptr<SpriteRegion>& region);
    std::shared_ptr<SpriteRegion> GetSpriteRegion() const;

};

}