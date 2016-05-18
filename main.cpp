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
#include "rapidxml_utils.hpp"
#include <oolua.h>

void test_production();

//OOLUA_PROXY(uint64_t)
//OOLUA_PROXY_END


int main(int argc, char** argv)
{
    World::LoadSavedWorld("data/world.xml");

    test_production();

    rapidxml::file<> f("test.lua");
    
    using namespace OOLUA; //NOLINT(build/namespaces)
    Script vm;
    vm.register_class<Territory>();
    vm.register_class<Country>();
    vm.register_class<World>();
    vm.register_class<Resource>();
    vm.register_class<Recipe>();
    vm.register_class<RecipeSlot>();
    vm.register_class<SlotList>();
    vm.register_class_static<Resource>("LoadResourceFile",
        &OOLUA::Proxy_class<Resource>::LoadResourceFile);
    vm.register_class_static<Resource>("GetResourceShortName",
        &OOLUA::Proxy_class<Resource>::GetResourceShortName);
    vm.register_class_static<Resource>("GetResourceByShortName",
        &OOLUA::Proxy_class<Resource>::GetResourceByShortName);
    vm.register_class_static<Resource>("GetResourceBaseValue",
        &OOLUA::Proxy_class<Resource>::GetResourceBaseValue);
    if(!run_chunk(vm, f.data()))
    {
        printf("LUA Error: '%s'\n", OOLUA::get_last_error(vm).c_str());
    }
    
    
    return 0;
}

void test_production()
{   
    printf("==========[Starting]==========\n");
    for(uint32_t ii=0; ii<500; ++ii)
    {
        World::GetWorldStrong()->Simulate();
        
        if(ii == 250)
        {
  //          australia->AddFactory();
        }
    }
    
    ISerializer::WriteToFile("world2.xml", World::GetWorldStrong().get());
}