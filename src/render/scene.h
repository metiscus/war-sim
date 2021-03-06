#pragma once

#include "camera.h"
#include "group.h"
#include "vector.h"
#include <vector>

namespace render 
{
    
    class Scene
    {
    private:
        Group root_;
        Camera camera_;
        
    public:
        Scene();
        // This object is not copyable
        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;
        // This object is movable
        Scene(Scene&&) = default;
        Scene& operator=(Scene&&) = default;
        Group& GetRoot();
        Camera& GetCamera();
        
        void Draw(float dt);

    };

}