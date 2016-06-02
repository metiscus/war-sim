#include "scene.h"

namespace render
{

    Scene::Scene()
    {
    }
    
    Group& Scene::GetRoot()
    {
        return root_;
    }
    
    Camera& Scene::GetCamera()
    {
        return camera_;
    }

    void Scene::Draw(float dt)
    {
        //dodad
    }
}