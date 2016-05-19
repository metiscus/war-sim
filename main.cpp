#include <fstream>
#include <iostream>
#include "world.h"
#include "rapidxml_utils.hpp"
#include <oolua.h>


int main(int argc, char** argv)
{
    std::string world_filename = "data/world.xml";
    if(argc == 1)
    {
        printf("Creating a new world from the default.\n");
    }
    else if(argc > 1)
    {
        world_filename = argv[1];
    }
    
    World::LoadSavedWorld(world_filename);
    
    auto world = World::GetWorldStrong();
    for(uint32_t i = 0; i<10; ++i)
    {
        world->Simulate();
    }
    
    return 0;
}