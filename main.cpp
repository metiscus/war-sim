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

void test_serialization();
void test_production();

struct ProductionDemand
{
    ResourceId id;
    uint64_t   qty;
};

int main(int argc, char** argv)
{
    test_serialization();
    test_production();
    
    return 0;
}

void test_production()
{
    std::vector<Recipe> recipes;

    std::ifstream file("recipes.dat");
    boost::archive::text_iarchive ia(file);
    ia>>recipes;
    
    std::shared_ptr<Stockpile> stockpile = std::make_shared<Stockpile>();
    stockpile->AddResource(resource_manpower, 8);
    stockpile->AddResource(resource_coal, 1000);
    stockpile->AddResource(resource_iron, 2000);
    
    std::vector<Factory> factories;
    factories.resize(3);
    factories[0].SetStockpile(stockpile);
    factories[0].SetRecipe(recipes[0]);
    factories[1].SetStockpile(stockpile);
    factories[1].SetRecipe(recipes[1]);
    factories[2].SetStockpile(stockpile);
    factories[2].SetRecipe(recipes[2]);
    
    stockpile->Debug();
    printf("==========[Starting]==========\n");
    for(uint32_t ii=0; ii<10; ++ii)
    {
        for(auto& factory : factories)
        {
            factory.GatherResources();
        }
        stockpile->Debug();
        for(auto& factory : factories)
        {
            factory.Produce();
        }
        for(auto& factory : factories)
        {
            factory.DeliverResources();
        }
        stockpile->Debug();
        printf("==========[Day: %lu]==========\n", ii);
    }
}

void test_serialization()
{
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