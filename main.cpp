#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include "factory.h"
#include "resource.h"
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
  //          australia->AddFactory();
        }
    }
    
    ISerializer::WriteToFile("world2.xml", g_world.get());
}

void world_init()
{
    // create a game world with some test provinces
#if 0
    g_world = World::CreateDefaultWorld();
    
    static const ResourceId farmland_id   = Resource::GetResourceByShortName("farmland");
    static const ResourceId energy_id     = Resource::GetResourceByShortName("energy");
    static const ResourceId lubricants_id = Resource::GetResourceByShortName("lubricants");
    static const ResourceId steel_id      = Resource::GetResourceByShortName("steel");
    static const ResourceId manpower_id   = Resource::GetResourceByShortName("manpower");
    static const ResourceId foodstuffs_id = Resource::GetResourceByShortName("foodstuffs");
    static const ResourceId machines_id   = Resource::GetResourceByShortName("machines");
    static const ResourceId coal_id       = Resource::GetResourceByShortName("coal");
    static const ResourceId iron_id       = Resource::GetResourceByShortName("iron");
    static const ResourceId crude_id      = Resource::GetResourceByShortName("crude");
    static const ResourceId rares_id      = Resource::GetResourceByShortName("rares");
    static const ResourceId fuel_id       = Resource::GetResourceByShortName("fuel");
    
    australia = std::make_shared<Country>(0, "Australia");
    australia->AddFactory();
    australia->AddFactory();
    australia->AddFactory();
    australia->AddFactory();
    auto stockpile = australia->GetStockpile();
    //stockpile->AddResource(resource_manpower, 5000);
    stockpile->AddResource(foodstuffs_id, 50000);
    stockpile->AddResource(energy_id, 1000);
    stockpile->AddResource(coal_id, 10000);
    stockpile->AddResource(iron_id, 2000);
    stockpile->AddResource(crude_id, 200);
    stockpile->AddResource(fuel_id, 50);
    stockpile->AddResource(rares_id, 5);
    stockpile->AddResource(lubricants_id, 5);
    stockpile->AddResource(machines_id, 50);
    g_world->AddCountry(australia);

    std::shared_ptr<Territory> territory = std::make_shared<Territory>(0, "Victoria", 0);
    territory->SetResource(coal_id, 8.0);
    territory->SetResource(farmland_id, 10.0, false);
    territory->SetResource(manpower_id, 440, false);
    territory->SetResource(foodstuffs_id, 400.0);
    g_world->AddTerritory(territory);
    australia->AddTerritory(g_world.get(), territory->GetId());
    
    territory = std::make_shared<Territory>(1, "New South Wales", 0);
    territory->SetResource(iron_id, 1.0);
    territory->SetResource(crude_id, 4.0);
    territory->SetResource(farmland_id, 10.0, false);
    territory->SetResource(foodstuffs_id, 470.0);
    territory->SetResource(manpower_id, 480, false);
    g_world->AddTerritory(territory);
    australia->AddTerritory(g_world.get(), territory->GetId());


    territory = std::make_shared<Territory>(2, "Queensland", 0);
    territory->SetResource(energy_id, 20.0);
    territory->SetResource(farmland_id, 10.0, false);
    territory->SetResource(foodstuffs_id, 250.0);
    territory->SetResource(manpower_id, 220, false);
    g_world->AddTerritory(territory);
    australia->AddTerritory(g_world.get(), territory->GetId());

    
    territory = std::make_shared<Territory>(3, "Northern Territory", 0);
    territory->SetResource(crude_id, 2.0);
    territory->SetResource(farmland_id, 10.0, false);
    territory->SetResource(foodstuffs_id, 13.0);
    territory->SetResource(manpower_id, 14, false);
    g_world->AddTerritory(territory);
    australia->AddTerritory(g_world.get(), territory->GetId());
    
    territory = std::make_shared<Territory>(4, "Western Australia", 0);
    territory->SetResource(rares_id, 1.0);
    territory->SetResource(farmland_id, 10.0, false);
    territory->SetResource(foodstuffs_id, 200.0);
    territory->SetResource(manpower_id, 220, false);
    g_world->AddTerritory(territory);
    australia->AddTerritory(g_world.get(), territory->GetId());

    territory = std::make_shared<Territory>(5, "Southern Australia", 0);
    territory->SetResource(iron_id, 1.0);
    territory->SetResource(energy_id, 5.0);
    territory->SetResource(farmland_id, 10.0, false);
    territory->SetResource(foodstuffs_id, 140.0);
    territory->SetResource(manpower_id, 130, false);
    g_world->AddTerritory(territory);
    australia->AddTerritory(g_world.get(), territory->GetId());
    
    
    ISerializer::WriteToFile("world.xml", g_world.get());
#endif
    g_world = World::LoadSavedWorld("data/world.xml");

}