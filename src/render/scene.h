#pragma once

#include "camera.h"
#include "vector.h"
#include <vector>

class Scene
{
private:
    Node root_;
    Camera camera_;
    
public:
    Node& GetRoot();
    Camera& GetCamera();
    
    void Draw(float dt);

};