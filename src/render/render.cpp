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
        SDL_Texture* surface_;
    public:
        explicit SurfaceWrapper(SDL_Texture* surface)
        {
            assert(surface);
            surface_ = surface;
        }
        
        SurfaceWrapper(const SurfaceWrapper&) = delete;
        SurfaceWrapper& operator=(const SurfaceWrapper&) = delete;
        
        ~SurfaceWrapper() { SDL_DestroyTexture(surface_); }
        
        inline SDL_Texture* Get() { return surface_; }
        
        typedef std::shared_ptr<SurfaceWrapper> Pointer;
    };
    
    class Canvas
    {
    private:
        std::unique_ptr<SurfaceWrapper> surface_;
    public:
        Canvas(std::unique_ptr<SurfaceWrapper>& surface)
        {
            surface_.reset(surface.release());
        }

        inline SDL_Texture* GetSurface() { return surface_->Get(); }
    };
    
    namespace
    {
        int32_t sheet_id_ = 0;
        std::unordered_map<int32_t, SurfaceWrapper::Pointer> surfaces_;
        std::unordered_map<int32_t, std::shared_ptr<SpriteSheet> > sheets_;
        std::unique_ptr<Canvas> canvas_;
        SDL_Window *window_ = nullptr;
        SDL_Renderer *renderer_ = nullptr;
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
    
    void CreateWindow(const char* title, uint32_t width, uint32_t height)
    {
        assert(!window_);
        if(!window_ && SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            assert(false);
        }
        
        SDL_CreateWindowAndRenderer(width, height, 0, &window_, &renderer_);
        SDL_SetWindowTitle(window_, title);
    }
    
    void ClearWindow()
    {
        assert(renderer_);
        if(renderer_)
        {
            SDL_RenderClear(renderer_);
        }
    }
    
    void DrawWindow(const std::vector<DrawOperation>& operations)
    {
        assert(renderer_);
        if(renderer_)
        {
            for(auto itr = operations.begin(); itr!=operations.end(); ++itr)
            {
                assert(surfaces_.count(itr->surface) > 0);
                auto surface = surfaces_[itr->surface];
                if(surface)
                {
                    SDL_Rect from;
                    from.x = itr->from_position.x;
                    from.y = itr->from_position.y;
                    from.w = itr->from_size.y;
                    from.h = itr->from_size.y;
                    SDL_Rect to;
                    to.x = itr->to_position.x;
                    to.y = itr->to_position.y;
                    to.w = itr->to_size.y;
                    to.h = itr->to_size.y;
                    SDL_RenderCopy(renderer_, surface->Get(), &from, &to);
                }
            }

            
        }
    }
        
    void PresentWindow()
    {
        SDL_RenderPresent(renderer_);
    }
}