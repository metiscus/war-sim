#include "spritesheet.h"

#include <cstdint>
#include <SDL2/SDL.h>
#include <unordered_map>
namespace render
{

class SpriteRegionImpl
{
    int32_t sheet_;
    SDL_Rect rect_;
public:
    SpriteRegionImpl()
    : sheet_(-1)
    { }

    inline void SetSheet(int32_t sheet) { sheet_ = sheet; }
    inline void SetRectangle(const SDL_Rect& rect) { rect_ = rect; }
    
    inline int32_t GetSheet() const { return sheet_; }
    inline const SDL_Rect& GetRect() const { return rect_; }
    
    friend class SpriteSheetImpl;
};

SpriteRegion::SpriteRegion()
{
    impl_ = new SpriteRegionImpl();
}

SpriteRegion::~SpriteRegion()
{
    delete impl_;
}

float SpriteRegion::GetWidth() const
{
    if(impl_) return impl_->GetRect().w;
    else return 0;
}

float SpriteRegion::GetHeight() const
{
    if(impl_) return impl_->GetRect().h;
    else return 0;
}

int32_t SpriteRegion::GetSheet() const
{
    if(impl_) return impl_->GetSheet();
    return -1;
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
class SpriteSheetImpl
{  
private:
    int32_t sheet_;
    std::unordered_map<std::string, std::shared_ptr<SpriteRegion> > region_;
    
public:
    SpriteSheetImpl()
    {
        sheet_ = -1;
    }

    inline void SetSheet(int32_t id) { sheet_ = id; }
    inline void AddRegion(const std::string& name, const SDL_Rect& rect)
    {
        auto region = std::make_shared<SpriteRegion>();
        region->impl_->SetSheet(sheet_);
        region_.emplace(std::make_pair(name, region));
    }

    inline std::shared_ptr<SpriteRegion> GetRegion(const std::string& name) const
    {
        std::shared_ptr<SpriteRegion> ret;
        auto itr = region_.find(name);
        if(itr != region_.end())
        {
            ret = itr->second;
        }
        return ret;
    }
};

SpriteSheet::SpriteSheet()
{
    impl_ = new SpriteSheetImpl();
}

SpriteSheet::~SpriteSheet()
{
    delete impl_;
}

std::shared_ptr<SpriteRegion> SpriteSheet::GetRegion(const std::string& name)
{
    std::shared_ptr<SpriteRegion> ret;
    if(impl_)
    {
        ret = impl_->GetRegion(name);
    }
    return ret;
}

void SpriteSheet::SetSheet(int32_t id)
{
    if(impl_)
    {
        impl_->SetSheet(id);
    }
}

}