#include "scriptbindings.h"

OOLUA_EXPORT_NO_FUNCTIONS(Resource)

OOLUA_EXPORT_FUNCTIONS(RecipeSlot)
OOLUA_EXPORT_FUNCTIONS_CONST(RecipeSlot
    ,GetResourceId
    ,GetQuantity
    ,GetIsConsumed
)

#if 1
OOLUA_EXPORT_FUNCTIONS(SlotList)
OOLUA_EXPORT_FUNCTIONS_CONST(SlotList, size)
//OOLUA_EXPORT_FUNCTIONS_CONST(SlotList
//    ,push_back
//    ,pop_back
//)
#else
OOLUA_EXPORT_NO_FUNCTIONS(SlotList)
#endif

OOLUA_EXPORT_FUNCTIONS(Recipe)
OOLUA_EXPORT_FUNCTIONS_CONST(Recipe
    ,ComputeOutputQty
    ,GetName
    ,GetInputs
    ,GetOutputs
)

OOLUA_EXPORT_FUNCTIONS(Territory
    ,SetOwner
    ,SetCore
    ,SetResource
    ,ChangeResource
)

OOLUA_EXPORT_FUNCTIONS_CONST(Territory
    ,GetId
    ,GetName
    ,GetOwner
    ,GetCore
    ,GetResource
    ,GetResourceIsProduced
)

OOLUA_EXPORT_FUNCTIONS(Country
    ,AddFactory
    ,RemoveFactory
    //,GetFactory
    ,AddTerritory
    ,RemoveTerritory
    ,GetStockpile
)

OOLUA_EXPORT_FUNCTIONS_CONST(Country
    ,GetId
    ,GetName
    ,GetFactoryCount
)

OOLUA_EXPORT_FUNCTIONS(Stockpile
    ,GetResource
    ,AddResource
)

OOLUA_EXPORT_FUNCTIONS_CONST(Stockpile
    ,ContainsResource
    ,GetResourceQuantity
    ,Debug
)

//OOLUA_EXPORT_NO_FUNCTIONS(World)
OOLUA_EXPORT_FUNCTIONS(World
    ,GetTerritory
    ,GetCountry
)

OOLUA_EXPORT_FUNCTIONS_CONST(World)

namespace Script
{
    
    std::shared_ptr<OOLUA::Script> CreateScriptEngine()
    {
        std::shared_ptr<OOLUA::Script> lua_ = std::make_shared<OOLUA::Script>();
        
        lua_->register_class<Territory>();
        lua_->register_class<Country>();
        lua_->register_class<World>();
        lua_->register_class<Resource>();
        lua_->register_class<Recipe>();
        lua_->register_class<RecipeSlot>();
        lua_->register_class<SlotList>();
        lua_->register_class<Stockpile>();
        lua_->register_class_static<Resource>("LoadResourceFile",
            &OOLUA::Proxy_class<Resource>::LoadResourceFile);
        lua_->register_class_static<Resource>("GetResourceShortName",
            &OOLUA::Proxy_class<Resource>::GetResourceShortName);
        lua_->register_class_static<Resource>("GetResourceByShortName",
            &OOLUA::Proxy_class<Resource>::GetResourceByShortName);
        lua_->register_class_static<Resource>("GetResourceBaseValue",
            &OOLUA::Proxy_class<Resource>::GetResourceBaseValue);
        
        lua_->register_class_static<World>("GetIntProperty",
            &OOLUA::Proxy_class<World>::GetIntProperty);
        lua_->register_class_static<World>("GetRealProperty",
            &OOLUA::Proxy_class<World>::GetRealProperty);
        lua_->register_class_static<World>("GetStringProperty",
            &OOLUA::Proxy_class<World>::GetStringProperty);

        lua_->register_class_static<World>("SetIntProperty",
            &OOLUA::Proxy_class<World>::SetIntProperty);
        lua_->register_class_static<World>("SetRealProperty",
            &OOLUA::Proxy_class<World>::SetRealProperty);
        lua_->register_class_static<World>("SetStringProperty",
            &OOLUA::Proxy_class<World>::SetStringProperty);

        lua_->register_class_static<World>("GetWorldStrong",
            &OOLUA::Proxy_class<World>::GetWorldStrong);
        
        return lua_;
    }    
}