#include "world.h"
#include <cstdio>
#include "rapidxml_utils.hpp"

World::World()
    : total_resources_(0)
{
    Resource::LoadResourceFile("data/resources.xml");

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
            AddRecipe(recipe);
        }
        node = node->next_sibling();
    }
}

void World::AddTerritory(std::shared_ptr<Territory> territory)
{
    auto itr = territories_.find(territory->GetId());
    if(itr != territories_.end())
    {
        territories_.erase(itr);
    }
    territories_.insert(std::make_pair(territory->GetId(), territory));
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

std::shared_ptr<Territory> World::GetTerritory(uint32_t id)
{
    std::shared_ptr<Territory> ret;
    auto itr = territories_.find(id);
    if(itr != territories_.end())
    {
        ret = itr->second;
    }
    return ret;
}

std::shared_ptr<Country> World::GetCountry(uint32_t id)
{
    std::shared_ptr<Country> ret;
    auto itr = countries_.find(id);
    if(itr != countries_.end())
    {
        ret = itr->second;
    }
    return ret;
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
    // do stuff 
    for(auto country : countries_)
    {
        country.second->SimulateDomestic(this);
        country.second->GatherResources(this);
    }
    
    for(auto country : countries_)
    {
        country.second->ProduceResources(this);
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
    }
    return true;
}