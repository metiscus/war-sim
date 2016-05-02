#include <boost/archive/text_iarchive.hpp> 
#include <boost/archive/text_oarchive.hpp> 
#include <fstream>
#include <iostream>
#include <memory>
#include "factory.h"
#include "resource_id.h"
#include "recipe.h"
#include "stockpile.h"

void test_serialization();
void test_production();

int main(int argc, char** argv)
{
    test_serialization();
    test_production();
    
    return 0;
}

void test_production()
{
    Recipe steel("steel from coal and iron");
    steel.AddInput(RecipeSlot (resource_coal, 1));
    steel.AddInput(RecipeSlot (resource_iron, 10));
    steel.AddOutput(RecipeSlot (resource_steel, 8));

    std::shared_ptr<Stockpile> stockpile = std::make_shared<Stockpile>();
    stockpile->AddResource(resource_coal, 1000);
    stockpile->AddResource(resource_iron, 2000);
    
    Factory factory;
    factory.SetStockpile(stockpile);
    factory.SetRecipe(steel);
    
    for(uint32_t ii=0; ii<10; ++ii)
    {
        factory.Simulate();
        stockpile->Debug();
    }
}

void test_serialization()
{
    Recipe steel("steel from coal and iron");
    steel.AddInput(RecipeSlot (resource_coal, 1));
    steel.AddInput(RecipeSlot (resource_iron, 10));
    steel.AddOutput(RecipeSlot (resource_steel, 8));
    
    
    std::ofstream file("recipe.dat");
    boost::archive::text_oarchive oa(file);
    oa << steel;
}