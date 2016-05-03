#include "world.h"

World::World()
{
    //HACK: for now we just hard code a few recipes in here
    auto energy = std::make_shared<Recipe>("energy from coal");
    energy->AddInput(RecipeSlot (resource_coal, 10));
    energy->AddInput(RecipeSlot (resource_manpower, 1, false));
    energy->AddOutput(RecipeSlot (resource_energy, 81));   
    AddRecipe(energy);

    auto crude = std::make_shared<Recipe>("crude oil from coal and electricity");
    crude->AddInput(RecipeSlot (resource_coal, 10));
    crude->AddInput(RecipeSlot (resource_manpower, 10, false));
    crude->AddInput(RecipeSlot (resource_energy, 50));  
    crude->AddOutput(RecipeSlot (resource_crude, 1));   
    AddRecipe(crude);
    
    auto coke = std::make_shared<Recipe>("coke from energy and coal");
    coke->AddInput(RecipeSlot (resource_coal, 10));
    coke->AddInput(RecipeSlot (resource_energy, 1));
    coke->AddInput(RecipeSlot (resource_manpower, 1, false));
    coke->AddOutput(RecipeSlot (resource_coke, 1));
    AddRecipe(coke);
    
    auto steel = std::make_shared<Recipe>("steel from coke, iron, and electricity");
    steel->AddInput(RecipeSlot (resource_manpower, 5, false));
    steel->AddInput(RecipeSlot (resource_energy, 100));
    steel->AddInput(RecipeSlot (resource_rares, 1));
    steel->AddInput(RecipeSlot (resource_coke, 1));
    steel->AddInput(RecipeSlot (resource_iron, 10));
    steel->AddOutput(RecipeSlot (resource_steel, 8));
    AddRecipe(steel);
    
    auto tools = std::make_shared<Recipe>("tools from iron, and electricity");
    tools->AddInput(RecipeSlot (resource_manpower, 10, false));
    tools->AddInput(RecipeSlot (resource_iron, 10));
    tools->AddOutput(RecipeSlot (resource_tools, 5));
    AddRecipe(tools);
    
    auto lubricants_fuel = std::make_shared<Recipe>("lubricants and fuel from oil and electricity");
    lubricants_fuel->AddInput(RecipeSlot (resource_manpower, 10, false));
    lubricants_fuel->AddInput(RecipeSlot (resource_crude, 10));
    lubricants_fuel->AddInput(RecipeSlot (resource_energy, 5));
    lubricants_fuel->AddOutput(RecipeSlot (resource_lubricants, 1));
    lubricants_fuel->AddOutput(RecipeSlot (resource_fuel, 8));
    AddRecipe(lubricants_fuel);
    
    auto bearings1 = std::make_shared<Recipe>("bearings from steel, lubricants, machines and electricity");
    bearings1->AddInput(RecipeSlot (resource_manpower, 18, false));
    bearings1->AddInput(RecipeSlot (resource_steel, 2));
    bearings1->AddInput(RecipeSlot (resource_lubricants, 1));
    bearings1->AddInput(RecipeSlot (resource_energy, 18));
    bearings1->AddInput(RecipeSlot (resource_machines, 10, false));
    bearings1->AddOutput(RecipeSlot (resource_bearings, 1));
    AddRecipe(bearings1);
    
    auto bearings2 = std::make_shared<Recipe>("bearings from steel, lubricants, tools and electricity");
    bearings2->AddInput(RecipeSlot (resource_manpower, 36, false));
    bearings2->AddInput(RecipeSlot (resource_steel, 3));
    bearings2->AddInput(RecipeSlot (resource_lubricants, 1));
    bearings2->AddInput(RecipeSlot (resource_energy, 20));
    bearings2->AddInput(RecipeSlot (resource_tools, 26, false));
    bearings2->AddOutput(RecipeSlot (resource_bearings, 1));
    AddRecipe(bearings2);
    
    auto machines = std::make_shared<Recipe>("machines from steel, bearings, tools, lubricants and electricity");
    machines->AddInput(RecipeSlot (resource_manpower, 20, false));
    machines->AddInput(RecipeSlot (resource_steel, 20));
    machines->AddInput(RecipeSlot (resource_lubricants, 1));
    machines->AddInput(RecipeSlot (resource_bearings, 1));
    machines->AddInput(RecipeSlot (resource_tools, 5, false));
    machines->AddOutput(RecipeSlot (resource_machines, 1));
    AddRecipe(machines);
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

void World::AddRecipe(RecipePtr ptr)
{
    recipes_.push_back(ptr);
    auto outputs = ptr->GetOutputs();
    for(RecipeSlot output : outputs)
    {
        if(output.GetIsConsumed())
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