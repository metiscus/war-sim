#pragma once
#include "recipe.h"
#include "resource.h"
#include "serializer.h"
#include "country.h"
#include "territory.h"
#include "world.h"

#include <memory>

#include <oolua.h>

OOLUA_PROXY(Resource)
    OOLUA_TAGS(No_public_constructors)
    OOLUA_SFUNC(LoadResourceFile)
    OOLUA_SFUNC(GetResourceShortName)
    OOLUA_SFUNC(GetResourceByShortName)
    OOLUA_SFUNC(GetResourceBaseValue)
OOLUA_PROXY_END

#if 1
OOLUA_PROXY(SlotList)
    //OOLUA_MEM_FUNC(void, push_back, const RecipeSlot&)
    //OOLUA_MFUNC(pop_back)
    OOLUA_MFUNC_CONST(size)
OOLUA_PROXY_END
#else
OOLUA_PROXY(SlotList)
OOLUA_PROXY_END
#endif

OOLUA_PROXY(RecipeSlot)
    OOLUA_TAGS(
        No_public_constructors
    )

    OOLUA_CTORS(
        OOLUA_CTOR(uint64_t, int64_t, bool)
    )

    OOLUA_MFUNC_CONST(GetResourceId)    
    OOLUA_MFUNC_CONST(GetQuantity)
    OOLUA_MFUNC_CONST(GetIsConsumed)
OOLUA_PROXY_END

OOLUA_PROXY(Stockpile)
    OOLUA_TAGS(
        No_default_constructor
    )
    
    OOLUA_MFUNC_CONST(ContainsResource)
    OOLUA_MFUNC(AddResource)
    OOLUA_MFUNC(GetResource)
    OOLUA_MFUNC_CONST(GetResourceQuantity)
    OOLUA_MFUNC_CONST(Debug)
OOLUA_PROXY_END

OOLUA_PROXY(Recipe)
    OOLUA_TAGS(
        No_public_constructors
    )

    OOLUA_CTORS(
        OOLUA_CTOR(const std::string&)
    )

    OOLUA_MFUNC_CONST(ComputeOutputQty)    
    OOLUA_MFUNC_CONST(GetName)
    OOLUA_MFUNC_CONST(GetInputs)
    OOLUA_MFUNC_CONST(GetOutputs)
    
//    OOLUA_MEM_FUNC(void, SetOwner, uint64_t)
//    OOLUA_MEM_FUNC(void, SetCore, uint64_t)
//    OOLUA_MEM_FUNC(void, SetResource, uint64_t, float, bool)
//    OOLUA_MEM_FUNC(void, ChangeResource, uint64_t, float)
OOLUA_PROXY_END

OOLUA_PROXY(Territory)    
    OOLUA_CTORS(
        OOLUA_CTOR(uint64_t, const std::string&, uint64_t)
    )

    OOLUA_MFUNC_CONST(GetId)    
    OOLUA_MFUNC_CONST(GetName)
    OOLUA_MFUNC_CONST(GetOwner)
    OOLUA_MFUNC_CONST(GetCore)
    OOLUA_MFUNC_CONST(GetResource)
    OOLUA_MFUNC_CONST(GetResourceIsProduced)
    
    OOLUA_MEM_FUNC(void, SetOwner, uint64_t)
    OOLUA_MEM_FUNC(void, SetCore, uint64_t)
    OOLUA_MEM_FUNC(void, SetResource, uint64_t, float, bool)
    OOLUA_MEM_FUNC(void, ChangeResource, uint64_t, float)
OOLUA_PROXY_END

OOLUA_PROXY(Country)
    OOLUA_TAGS(
        No_default_constructor
    )

    OOLUA_CTORS(
        OOLUA_CTOR(uint64_t, const std::string&)
    )

    OOLUA_MFUNC_CONST(GetId)    
    OOLUA_MFUNC_CONST(GetName)
    OOLUA_MFUNC(GetStockpile)
    OOLUA_MFUNC_CONST(GetFactoryCount)
    //OOLUA_MFUNC_CONST(GetFactory)
    //OOLUA_MFUNC_CONST(GetTerritories)
    
    OOLUA_MFUNC(AddFactory)
    OOLUA_MFUNC(RemoveFactory)
    //OOLUA_MFUNC(GetFactory)
    OOLUA_MFUNC(AddTerritory)
    OOLUA_MFUNC(RemoveTerritory)
    //OOLUA_MFUNC(GatherResources)
    //OOLUA_MFUNC(ProduceResources)
    //OOLUA_MFUNC(SimulateDomestic)
OOLUA_PROXY_END

OOLUA_PROXY(World)
    OOLUA_TAGS(
        No_public_constructors
    )

    OOLUA_MFUNC(GetCountry)
    OOLUA_MFUNC(GetTerritory)
    OOLUA_SFUNC(GetWorldStrong)
    OOLUA_SFUNC(GetIntProperty)
    OOLUA_SFUNC(GetRealProperty)
    OOLUA_SFUNC(GetStringProperty)
    OOLUA_SFUNC(SetIntProperty)
    OOLUA_SFUNC(SetRealProperty)
    OOLUA_SFUNC(SetStringProperty)
OOLUA_PROXY_END


namespace Script
{
    typedef OOLUA::Script Engine;

    std::shared_ptr<Engine> CreateScriptEngine();
}