#pragma once

#include <map>
#include <memory>
#include <string>

#include "recipe.h"
#include "resource.h"
#include "serializer.h"

#include <oolua.h>

class World;
class Country;
class Territory;

typedef std::weak_ptr<World> WorldWeakPtr;
typedef std::shared_ptr<World> WorldPtr;

class World : public ISerializer
{
private:
    static WorldPtr s_world_;
    std::map<uint64_t, Resource> resources_;
    
    std::map<uint32_t, std::shared_ptr<Territory> > territories_;
    std::map<uint32_t, std::shared_ptr<Country> > countries_;

    std::vector<RecipePtr> recipes_;
    std::multimap<ResourceId, RecipePtr> recipe_map_;

    World();
public:
    static void CreateDefaultWorld();
    static void LoadSavedWorld(const std::string& name);

    void AddTerritory(std::shared_ptr<Territory> territory);
    void AddCountry(std::shared_ptr<Country> country);
    std::shared_ptr<Territory> GetTerritory(uint32_t id);
    std::shared_ptr<Country> GetCountry(uint32_t id);   
    
    void AddRecipe(RecipePtr ptr);
    std::vector<RecipePtr> GetRecipesForResource(ResourceId id);
    
    void Simulate();
    
    virtual bool ReadInstance(ISerializer::Node* node);
    virtual bool WriteInstance(ISerializer::Node* node);
    
    
    static WorldWeakPtr GetWorld();
    static WorldPtr     GetWorldStrong();
};

OOLUA_PROXY(World)
    OOLUA_TAGS(
        No_public_constructors
    )
OOLUA_PROXY_END