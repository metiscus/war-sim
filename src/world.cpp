#include "world.h"
#include <cstdio>
#include <functional>
#include "rapidxml_utils.hpp"
#include "territory.h"
#include "country.h"
#include "stockpile.h"
#include "territorymanager.h"
#include "scriptbindings.h"

WorldPtr World::s_world_;

World::World()
{
    lua_ = Script::CreateScriptEngine();
    property_map_["day"].SetInteger(0);
}

int64_t World::GetIntProperty(const char* name)
{
    return s_world_->property_map_[std::string(name)].GetInteger();
}

double World::GetRealProperty(const char* name)
{
    return s_world_->property_map_[std::string(name)].GetReal();
}

std::string World::GetStringProperty(const char* name)
{
    return s_world_->property_map_[std::string(name)].GetString();
}

void World::SetIntProperty(const char* name, int64_t value)
{
    s_world_->property_map_[std::string(name)].SetInteger(value);
}

void World::SetRealProperty(const char* name, double value)
{
    s_world_->property_map_[std::string(name)].SetReal(value);
}

void World::SetStringProperty(const char* name, const char* value)
{
    s_world_->property_map_[std::string(name)].SetString(value);
}

void World::CreateDefaultWorld()
{
    s_world_.reset(new World());
    
    // Load default resources
    Resource::LoadResourceFile("data/resources.xml");
    s_world_->resources_ = Resource::s_resources_;

    // Load default recipes
    rapidxml::file<> f("data/recipes.xml");
    rapidxml::xml_document<> d;
    d.parse<0>(f.data());
    
    auto node = d.first_node();
    if(node) node = node->first_node();
    while(node != nullptr)
    {
        auto recipe = std::make_shared<Recipe>();
        if(recipe->ReadInstance(node))
        {
            s_world_->AddRecipe(recipe);
        }
        node = node->next_sibling();
    }
    
    if(!s_world_->lua_->run_file("data/world.lua"))
    {
        printf("LUA Error: '%s'\n", OOLUA::get_last_error(*(s_world_->lua_)).c_str());
    }
}

void World::LoadSavedWorld(const std::string& name)
{
    s_world_.reset(new World());
    Resource::LoadResourceFile("data/resources.xml");

    rapidxml::file<> f(name.c_str());
    rapidxml::xml_document<> d;
    d.parse<0>(f.data());
    Node *node = d.first_node();
    if(node) node = node->first_node();
    s_world_->ReadInstance(node);
    
    if(!s_world_->lua_->run_file("data/world.lua"))
    {
        printf("LUA Error: '%s'\n", OOLUA::get_last_error(*(s_world_->lua_)).c_str());
    }
}

void World::AddTerritory(std::shared_ptr<Territory> territory)
{
    TerritoryManager::AddTerritory(territory);
}

void World::AddCountry(std::shared_ptr<Country> country)
{
    auto itr = countries_.find(country->GetId());
    if(itr != countries_.end())
    {
        countries_.erase(itr);
    }
    countries_.insert(std::make_pair(country->GetId(), country));
    
}

Territory* World::GetTerritory(uint32_t id)
{
    return TerritoryManager::GetTerritoryByIdRw(id);
}

Country* World::GetCountry(uint32_t id)
{
    std::shared_ptr<Country> ret;
    auto itr = countries_.find(id);
    if(itr != countries_.end())
    {
        ret = itr->second;
    }
    return ret.get();
}

void World::AddRecipe(RecipePtr ptr)
{
    recipes_.push_back(ptr);
    auto outputs = ptr->GetOutputs();
    for(RecipeSlot output : outputs)
    {
        if(output.GetIsConsumed())
        {
            recipe_map_.insert(std::make_pair(output.GetResourceId(), ptr));
        }
    }
}

std::vector<RecipePtr> World::GetRecipesForResource(ResourceId id)
{
    auto upper = recipe_map_.upper_bound(id);
    auto lower = recipe_map_.lower_bound(id);
    std::vector<RecipePtr> ret;
    while(lower != upper)
    {
        ret.push_back(lower->second);
        ++lower;
    }
    return ret;
}

void World::Simulate()
{
    property_map_["day"].SetInteger(property_map_["day"].GetInteger() + 1); 
    
    OOLUA::Lua_function Caller(*lua_);
    Caller("OnSimulate");
    
    // do stuff 
    for(auto country : countries_)
    {
        country.second->SimulateDomestic();
        country.second->GatherResources();
    }
    
    for(auto country : countries_)
    {
        country.second->ProduceResources();
    }
}

bool World::ReadInstance(ISerializer::Node* node)
{
    auto resources = FindChildNode(node, "resources");
    if(resources)
    {
        ForAllChildren(resources, [this] (ISerializer::Node* node) {
            Resource r;
            r.ReadInstance(node);
            resources_.insert(std::make_pair(r.GetId(), r));
        });
    }
    
    auto recipes = FindChildNode(node, "recipes");
    if(recipes)
    {
        ForAllChildren(recipes, [this] (ISerializer::Node* node) {
            RecipePtr ptr = std::make_shared<Recipe>();
            if(ptr->ReadInstance(node))
            {
                AddRecipe(ptr);
            }
        });
    }
    
    auto countries = FindChildNode(node, "countries");
    if(countries)
    {
        ForAllChildren(countries, [this] (ISerializer::Node* node) {
            auto ptr = std::make_shared<Country>();
            if(ptr->ReadInstance(node))
            {
                AddCountry(ptr);
            }
        });
    }
    
    auto territories = FindChildNode(node, "territories");
    if(territories)
    {
        ForAllChildren(territories, [this] (ISerializer::Node* node) {
            auto ptr = std::make_shared<Territory>();
            if(ptr->ReadInstance(node))
            {
                AddTerritory(ptr);
            }
        });
    }    

    return true;
}

bool World::WriteInstance(ISerializer::Node* node)
{
    auto world_node = CreateChildNode(node, "world");
    if(world_node)
    {
        auto resources = CreateChildNode(world_node, "resources");
        if(resources)
        {
            for(auto itr: resources_)
            {
                itr.second.WriteInstance(resources);
            }
        }
        
        auto recipes = CreateChildNode(world_node, "recipes");
        if(recipes)
        {
            for(auto itr: recipes_)
            {
                itr->WriteInstance(recipes);
            }
        }
        
        auto countries = CreateChildNode(world_node, "countries");
        {            
            for(auto itr: countries_)
            {
                itr.second->WriteInstance(countries);
            }
        }
        
#if 0
        auto territories = CreateChildNode(world_node, "territories");
        {
            for(auto itr: territories_)
            {
                itr.second->WriteInstance(territories);
            }
        }
#endif
    }
    return true;
}

WorldWeakPtr World::GetWorld()
{
    WorldWeakPtr ret = s_world_;
    return ret;
}

World* World::GetWorldStrong()
{
    return s_world_.get();
}