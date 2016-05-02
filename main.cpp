#include <boost/archive/text_iarchive.hpp> 
#include <boost/archive/text_oarchive.hpp> 
#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include "factory.h"
#include "resource_id.h"
#include "recipe.h"
#include "stockpile.h"
#include "country.h"
#include "territory.h"
#include "world.h"

void world_init();
void test_production();

std::shared_ptr<World> g_world;

struct ProductionDemand
{
    ResourceId id;
    uint64_t   qty;
};

int main(int argc, char** argv)
{
    world_init();
    test_production();
    
    return 0;
}

void test_production()
{
    std::vector<Recipe> recipes;

    std::ifstream file("recipes.dat");
    boost::archive::text_iarchive ia(file);
    ia>>recipes;
    
    printf("==========[Starting]==========\n");
    for(uint32_t ii=0; ii<10; ++ii)
    {
        g_world->Simulate();
    }
}

void world_init()
{
    // create a game world with some test provinces
    g_world = std::make_shared<World>();
    auto australia = std::make_shared<Country>(0, "Australia");
    australia->AddFactory();
    australia->AddFactory();
    australia->AddFactory();
    auto stockpile = australia->GetStockpile();
    stockpile->AddResource(resource_manpower, 5000000);
    stockpile->AddResource(resource_energy, 1000);
    stockpile->AddResource(resource_coal, 10000);
    stockpile->AddResource(resource_iron, 2000);
    g_world->AddCountry(australia);

    std::shared_ptr<Territory> territory = std::make_shared<Territory>(0, "Victoria", 0);
    {
        auto &resources = territory->GetResources();
        resources.SetResource(resource_coal, 5.0);
        //resources.SetResource(resource_manpower, 15.0);
        g_world->AddTerritory(territory);
        australia->AddTerritory(territory->GetId());
    }
    
    territory = std::make_shared<Territory>(1, "New South Wales", 0);
    {
        auto &resources = territory->GetResources();
        resources.SetResource(resource_iron, 1.0);
        //resources.SetResource(resource_manpower, 5.0);
        g_world->AddTerritory(territory);
        australia->AddTerritory(territory->GetId());
    }
    

    // Roughly 10 tons of coal will create 81MWh of power
    Recipe energy("energy from coal");
    energy.AddInput(RecipeSlot (resource_coal, 10));
    energy.AddInput(RecipeSlot (resource_manpower, 1, false));
    energy.AddOutput(RecipeSlot (resource_energy, 81));    
    
    Recipe coke("coke from energy and coal");
    coke.AddInput(RecipeSlot (resource_coal, 10));
    coke.AddInput(RecipeSlot (resource_energy, 1));
    coke.AddInput(RecipeSlot (resource_manpower, 1, false));
    coke.AddOutput(RecipeSlot (resource_coke, 1));
    
    Recipe steel("steel from coke, iron, and electricity");
    steel.AddInput(RecipeSlot (resource_manpower, 5, false));
    steel.AddInput(RecipeSlot (resource_energy, 100));
    steel.AddInput(RecipeSlot (resource_coke, 1));
    steel.AddInput(RecipeSlot (resource_iron, 10));
    steel.AddOutput(RecipeSlot (resource_steel, 8));

// Idea for economy planning    
//    std::multimap<ResourceId, Recipe> recipes;
//    recipes.insert(std::make_pair(resource_energy, energy));
//    recipes.insert(std::make_pair(resource_coke, coke));
//    recipes.insert(std::make_pair(resource_steel, steel));
    
    std::vector<Recipe> recipes;
    recipes.push_back(energy);
    recipes.push_back(coke);
    recipes.push_back(steel);
    std::ofstream file("recipes.dat");
    boost::archive::text_oarchive oa(file);
    oa<<recipes;
    file.close();
}