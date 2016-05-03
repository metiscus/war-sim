#include "world.h"

World::World()
{
    //HACK: for now we just hard code a few recipes in here
    auto energy = std::make_shared<Recipe>("energy from coal");
    energy->AddInput(RecipeSlot (resource_coal, 10));
    energy->AddInput(RecipeSlot (resource_manpower, 1, false));
    energy->AddOutput(RecipeSlot (resource_energy, 81));   
    AddRecipe(energy);
    
    auto coke = std::make_shared<Recipe>("coke from energy and coal");
    coke->AddInput(RecipeSlot (resource_coal, 10));
    coke->AddInput(RecipeSlot (resource_energy, 1));
    coke->AddInput(RecipeSlot (resource_manpower, 1, false));
    coke->AddOutput(RecipeSlot (resource_coke, 1));
    AddRecipe(coke);
    
    auto steel = std::make_shared<Recipe>("steel from coke, iron, and electricity");
    steel->AddInput(RecipeSlot (resource_manpower, 5, false));
    steel->AddInput(RecipeSlot (resource_energy, 100));
    steel->AddInput(RecipeSlot (resource_coke, 1));
    steel->AddInput(RecipeSlot (resource_iron, 10));
    steel->AddOutput(RecipeSlot (resource_steel, 8));
    AddRecipe(steel);
}

void World::AddTerritory(std::shared_ptr<Territory> territory)
{
    auto itr = territories_.find(territory->GetId());
    if(itr != territories_.end())
    {
        territories_.erase(itr);

    }
    territories_.insert(std::make_pair(territory->GetId(), territory));
}

void World::AddCountry(std::shared_ptr<Country> country)
{
    auto itr = countries_.find(country->GetId());
    if(itr != countries_.end())
    {
        countries_.erase(itr);
    }
    countries_.insert(std::make_pair(country->GetId(), country));
    
}

std::shared_ptr<Territory> World::GetTerritory(uint32_t id)
{
    std::shared_ptr<Territory> ret;
    auto itr = territories_.find(id);
    if(itr != territories_.end())
    {
        ret = itr->second;
    }
    return ret;
}

std::shared_ptr<Country> World::GetCountry(uint32_t id)
{
    std::shared_ptr<Country> ret;
    auto itr = countries_.find(id);
    if(itr != countries_.end())
    {
        ret = itr->second;
    }
    return ret;
}

void World::Simulate()
{
    // do stuff 
    for(auto country : countries_)
    {
        country.second->GatherResources(this);
    }
    
    for(auto country : countries_)
    {
        country.second->ProduceResources(this);
    }
}

void World::AddRecipe(RecipePtr ptr)
{
    recipes_.push_back(ptr);
    auto outputs = ptr->GetOutputs();
    for(RecipeSlot output : outputs)
    {
        if(output.GetResourceId() != resource_manpower)
        {
            recipe_map_.insert(std::make_pair(output.GetResourceId(), ptr));
        }
    }
}

std::vector<RecipePtr> World::GetRecipesForResource(ResourceId id)
{
    auto upper = recipe_map_.upper_bound(id);
    auto lower = recipe_map_.lower_bound(id);
    std::vector<RecipePtr> ret;
    while(lower != upper)
    {
        ret.push_back(lower->second);
        ++lower;
    }
    return ret;
}