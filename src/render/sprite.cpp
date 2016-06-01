#include "sprite.h"

namespace render
{
   
void Sprite::SetSpriteRegion(const std::shared_ptr<SpriteRegion>& region)
{
    region_ = region;
}

std::shared_ptr<SpriteRegion> Sprite::GetSpriteRegion() const
{
    return region_;
}

}