#include "render.h"
#include <cassert>
#include <memory>
#include <SDL2/SDL.h>
#include "spritesheet.h"
#include <unordered_map>

namespace render 
{
    class SurfaceWrapper;
    class SurfaceWrapper
    {
        SDL_Surface* surface_;
    public:
        explicit SurfaceWrapper(SDL_Surface* surface)
        {
            assert(surface);
            surface_ = surface;
        }
        
        SurfaceWrapper(const SurfaceWrapper&) = delete;
        SurfaceWrapper& operator=(const SurfaceWrapper&) = delete;
        
        ~SurfaceWrapper() { SDL_FreeSurface(surface_); }
        
        inline SDL_Surface* Get() { return surface_; }
        
        typedef std::shared_ptr<SurfaceWrapper> Pointer;
    };
    
    namespace
    {
        int32_t sheet_id_ = 0;
        std::unordered_map<int32_t, SurfaceWrapper::Pointer> surfaces_;
        std::unordered_map<int32_t, std::shared_ptr<SpriteSheet> > sheets_;
    }
    
    int32_t LoadSpriteSheet(const std::string& filename, const std::string& name)
    {
        assert(false);
        
        int32_t ret = sheet_id_++;
        
        
        // Insert the new sheet into the map
        auto sheet = std::make_shared<SpriteSheet>();
        sheet->SetSheet(ret);
        sheets_.emplace(std::make_pair(ret, sheet));
        
        return ret;
    }
}