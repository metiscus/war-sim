#pragma once

#include "camera.h"
#include "vector.h"
#include <vector>

namespace render 
{
    
    class Scene
    {
    private:
        Node root_;
        Camera camera_;
        
    public:
        Scene();
        Node& GetRoot();
        Camera& GetCamera();
        
        void Draw(float dt);

    };

}