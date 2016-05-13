#pragma once

#include <boost/archive/text_iarchive.hpp> 
#include <boost/archive/text_oarchive.hpp> 

#include <map>
#include <memory>

#include "recipe.h"
#include "resource.h"
#include "country.h"
#include "territory.h"


class World
{
    friend class boost::serialization::access;
private:
    
    std::map<uint64_t, Resource> resources_;
    
    std::map<uint32_t, std::shared_ptr<Territory> > territories_;
    std::map<uint32_t, std::shared_ptr<Country> > countries_;

    std::vector<RecipePtr> recipes_;
    std::multimap<ResourceId, RecipePtr> recipe_map_;
    std::map<ResourceId, uint64_t> global_static_resources_;
    std::map<ResourceId, float> global_static_resource_scarcity_;
    uint64_t total_resources_;

public:
    World();

    void AddTerritory(std::shared_ptr<Territory> territory);
    void AddCountry(std::shared_ptr<Country> country);
    std::shared_ptr<Territory> GetTerritory(uint32_t id);
    std::shared_ptr<Country> GetCountry(uint32_t id);   
    
    void AddRecipe(RecipePtr ptr);
    std::vector<RecipePtr> GetRecipesForResource(ResourceId id);
    
    void Simulate();
    
};