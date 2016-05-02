#include <boost/archive/text_iarchive.hpp> 
#include <boost/archive/text_oarchive.hpp> 
#include <fstream>
#include <iostream>
#include "resource_id.h"
#include "recipe.h"

int main(int argc, char** argv)
{
    Recipe steel("steel from coal");
    steel.AddInput(RecipeSlot (resource_coal, 1));
    steel.AddInput(RecipeSlot (resource_iron, 10));
    steel.AddOutput(RecipeSlot (resource_steel, 8));
    
    
    std::ofstream file("recipe.dat");
    boost::archive::text_oarchive oa(file);
    oa << steel;

    return 0;
}