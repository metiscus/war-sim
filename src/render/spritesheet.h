#pragma once
#include <memory>
#include <string>

namespace render
{

class SpriteRegionImpl;
class SpriteRegion
{
private:
    SpriteRegionImpl* impl_;;

public:
    explicit SpriteRegion();
    SpriteRegion(const SpriteRegion&) = delete;
    SpriteRegion& operator=(const SpriteRegion&) = delete;

    ~SpriteRegion();
    
    float GetWidth() const;
    float GetHeight() const;
    int32_t GetSheet() const;
    
    friend class SpriteSheetImpl;
};

class SpriteSheetImpl;
class SpriteSheet
{
private:
    SpriteSheetImpl* impl_;

public:
    explicit SpriteSheet();
    ~SpriteSheet();
    SpriteSheet(const SpriteSheet&) = delete;
    SpriteSheet& operator=(const SpriteSheet&) = delete;
    
    void SetSheet(int32_t id);
    std::shared_ptr<SpriteRegion> GetRegion(const std::string& name);
};
}