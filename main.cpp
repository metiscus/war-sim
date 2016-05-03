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

std::shared_ptr<Country> australia;
void test_production()
{   
    printf("==========[Starting]==========\n");
    for(uint32_t ii=0; ii<500; ++ii)
    {
        g_world->Simulate();
        
        if(ii == 250)
        {
            australia->AddFactory();
        }
    }
}

void world_init()
{
    // create a game world with some test provinces
    g_world = std::make_shared<World>();
    australia = std::make_shared<Country>(0, "Australia");
    australia->AddFactory();
    australia->AddFactory();
    australia->AddFactory();
    australia->AddFactory();
    auto stockpile = australia->GetStockpile();
    stockpile->AddResource(resource_manpower, 5000);
    stockpile->AddResource(resource_foodstuffs, 50000);
    stockpile->AddResource(resource_energy, 1000);
    stockpile->AddResource(resource_coal, 10000);
    stockpile->AddResource(resource_iron, 2000);
    stockpile->AddResource(resource_crude, 200);
    stockpile->AddResource(resource_fuel, 50);
    stockpile->AddResource(resource_rares, 5);
    stockpile->AddResource(resource_lubricants, 5);
    stockpile->AddResource(resource_machines, 50);
    g_world->AddCountry(australia);

    std::shared_ptr<Territory> territory = std::make_shared<Territory>(0, "Victoria", 0);
    {
        auto &resources = territory->GetResources();
        resources.SetResource(resource_coal, 8.0);
        g_world->AddTerritory(territory);
        australia->AddTerritory(g_world.get(), territory->GetId());
    }
    
    territory = std::make_shared<Territory>(1, "New South Wales", 0);
    {
        auto &resources = territory->GetResources();
        resources.SetResource(resource_iron, 1.0);
        resources.SetResource(resource_crude, 1.0);
        resources.SetResource(resource_farmland, 10.0, false);
        resources.SetResource(resource_foodstuffs, 800.0);
        g_world->AddTerritory(territory);
        australia->AddTerritory(g_world.get(), territory->GetId());
    }

    territory = std::make_shared<Territory>(2, "Queensland", 0);
    {
        auto &resources = territory->GetResources();
        resources.SetResource(resource_energy, 20.0);
        resources.SetResource(resource_farmland, 10.0, false);
        resources.SetResource(resource_foodstuffs, 800.0);
        g_world->AddTerritory(territory);
        australia->AddTerritory(g_world.get(), territory->GetId());
    }
    
    territory = std::make_shared<Territory>(3, "Northern Territory", 0);
    {
        auto &resources = territory->GetResources();
        resources.SetResource(resource_crude, 1.0);
        resources.SetResource(resource_farmland, 10.0, false);
        resources.SetResource(resource_foodstuffs, 800.0);
        g_world->AddTerritory(territory);
        australia->AddTerritory(g_world.get(), territory->GetId());
    }
    
    territory = std::make_shared<Territory>(4, "Western Australia", 0);
    {
        auto &resources = territory->GetResources();
        resources.SetResource(resource_rares, 1.0);
        resources.SetResource(resource_farmland, 10.0, false);
        resources.SetResource(resource_foodstuffs, 800.0);
        g_world->AddTerritory(territory);
        australia->AddTerritory(g_world.get(), territory->GetId());
    }
    
    territory = std::make_shared<Territory>(5, "Southern Australia", 0);
    {
        auto &resources = territory->GetResources();
        resources.SetResource(resource_iron, 1.0);
        resources.SetResource(resource_energy, 5.0);
        resources.SetResource(resource_farmland, 10.0, false);
        resources.SetResource(resource_foodstuffs, 800.0);
        g_world->AddTerritory(territory);
        australia->AddTerritory(g_world.get(), territory->GetId());
    }
}