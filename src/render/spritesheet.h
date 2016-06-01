#pragma once
#include <memory>
#include <string>

namespace render
{

class SpriteRegionImpl;
class SpriteRegion
{
private:
    std::unique_ptr<SpriteRegionImpl> impl_;

public:
    SpriteRegion();
    float GetWidth() const;
    float GetHeight() const;
    
    friend class SpriteSheetImpl;
};

class SpriteSheetImpl;
class SpriteSheet
{
private:
    std::unique_ptr<SpriteSheetImpl> impl_;

public:
    SpriteSheet();
    void SetSheet(int32_t id);
    std::shared_ptr<SpriteRegion> GetRegion(const std::string& name);
};
}