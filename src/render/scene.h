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
        Group& GetRoot();
        Camera& GetCamera();
        
        void Draw(float dt);

    };

}