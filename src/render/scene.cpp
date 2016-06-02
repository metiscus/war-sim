#include "scene.h"
#include "sprite.h"

namespace render
{
    class SceneVisitor : public NodeVisitor
    {
    public:
        virtual void Visit(Node& node)
        {
            
        }
        
        virtual void Visit(Sprite& node)
        {
            //convert sprite -> draw command
            
        }
    };
    
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