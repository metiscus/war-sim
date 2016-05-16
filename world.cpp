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
    
    auto node = d.first_node("recipe");
    while(node != nullptr)
    {
        auto recipe = std::make_shared<Recipe>();
        if(recipe->ReadInstance(node))
        {
            AddRecipe(recipe);
        }
        node = node->next_sibling();
    }
#if 0    
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
    static const ResourceId tools_id      = Resource::GetResourceByShortName("tools");
    static const ResourceId bearings_id   = Resource::GetResourceByShortName("bearings");
    static const ResourceId coke_id       = Resource::GetResourceByShortName("coke");
    
    //HACK: for now we just hard code a few recipes in here  
    //TODO: ideally the system would select the one that is "best"
    auto food = std::make_shared<Recipe>("food from farmland and manpower");
    food->AddInput(RecipeSlot (farmland_id, 10, false));
    food->AddInput(RecipeSlot (manpower_id, 200, false));
    food->AddOutput(RecipeSlot (foodstuffs_id, 1000));   
    AddRecipe(food);
    
    auto energy1 = std::make_shared<Recipe>("energy from coal");
    energy1->AddInput(RecipeSlot (coal_id, 10));
    energy1->AddInput(RecipeSlot (manpower_id, 1, false));
    energy1->AddOutput(RecipeSlot (energy_id, 81));   
    AddRecipe(energy1);
    
    auto energy2 = std::make_shared<Recipe>("energy from fuel");
    energy2->AddInput(RecipeSlot (fuel_id, 10));
    energy2->AddInput(RecipeSlot (manpower_id, 20, false));
    energy2->AddOutput(RecipeSlot (energy_id, 1000));   
    AddRecipe(energy2);
    
    auto crude = std::make_shared<Recipe>("crude oil from coal and energy");
    crude->AddInput(RecipeSlot (coal_id, 10));
    crude->AddInput(RecipeSlot (manpower_id, 10, false));
    crude->AddInput(RecipeSlot (energy_id, 50));  
    crude->AddOutput(RecipeSlot (crude_id, 1));   
    AddRecipe(crude);
    
    auto coke = std::make_shared<Recipe>("coke from energy and coal");
    coke->AddInput(RecipeSlot (coal_id, 10));
    coke->AddInput(RecipeSlot (energy_id, 1));
    coke->AddInput(RecipeSlot (manpower_id, 1, false));
    coke->AddOutput(RecipeSlot (coke_id, 1));
    AddRecipe(coke);
    
    auto steel = std::make_shared<Recipe>("steel from coke, iron, and energy");
    steel->AddInput(RecipeSlot (manpower_id, 5, false));
    steel->AddInput(RecipeSlot (energy_id, 100));
    steel->AddInput(RecipeSlot (rares_id, 1));
    steel->AddInput(RecipeSlot (coke_id, 1));
    steel->AddInput(RecipeSlot (iron_id, 10));
    steel->AddOutput(RecipeSlot (steel_id, 8));
    AddRecipe(steel);
    
    auto tools = std::make_shared<Recipe>("tools from iron, and energy");
    tools->AddInput(RecipeSlot (manpower_id, 10, false));
    tools->AddInput(RecipeSlot (iron_id, 10));
    tools->AddOutput(RecipeSlot (tools_id, 5));
    AddRecipe(tools);
    
    auto lubricants_fuel = std::make_shared<Recipe>("lubricants and fuel from oil and energy");
    lubricants_fuel->AddInput(RecipeSlot (manpower_id, 10, false));
    lubricants_fuel->AddInput(RecipeSlot (crude_id, 10));
    lubricants_fuel->AddInput(RecipeSlot (energy_id, 5));
    lubricants_fuel->AddOutput(RecipeSlot (lubricants_id, 1));
    lubricants_fuel->AddOutput(RecipeSlot (fuel_id, 8));
    AddRecipe(lubricants_fuel);
    
    auto bearings1 = std::make_shared<Recipe>("bearings from steel, lubricants, machines and energy");
    bearings1->AddInput(RecipeSlot (manpower_id, 20, false));
    bearings1->AddInput(RecipeSlot (steel_id, 4));
    bearings1->AddInput(RecipeSlot (lubricants_id, 2));
    bearings1->AddInput(RecipeSlot (energy_id, 25));
    bearings1->AddInput(RecipeSlot (machines_id, 10, false));
    bearings1->AddOutput(RecipeSlot (bearings_id, 2));
    AddRecipe(bearings1);
    
    auto bearings2 = std::make_shared<Recipe>("bearings from steel, lubricants, tools and energy");
    bearings2->AddInput(RecipeSlot (manpower_id, 36, false));
    bearings2->AddInput(RecipeSlot (steel_id, 3));
    bearings2->AddInput(RecipeSlot (lubricants_id, 1));
    bearings2->AddInput(RecipeSlot (energy_id, 20));
    bearings2->AddInput(RecipeSlot (tools_id, 26, false));
    bearings2->AddOutput(RecipeSlot (bearings_id, 1));
    AddRecipe(bearings2);
    
    auto machines = std::make_shared<Recipe>("machines from steel, bearings, tools, lubricants and energy");
    machines->AddInput(RecipeSlot (manpower_id, 20, false));
    machines->AddInput(RecipeSlot (steel_id, 20));
    machines->AddInput(RecipeSlot (lubricants_id, 1));
    machines->AddInput(RecipeSlot (bearings_id, 1));
    machines->AddInput(RecipeSlot (tools_id, 5, false));
    machines->AddInput(RecipeSlot (energy_id, 20));
    machines->AddOutput(RecipeSlot (machines_id, 1));
    AddRecipe(machines);
    
    auto machines2 = std::make_shared<Recipe>("machines from steel, bearings, machines, lubricants and energy");
    machines2->AddInput(RecipeSlot (manpower_id, 20, false));
    machines2->AddInput(RecipeSlot (steel_id, 40));
    machines2->AddInput(RecipeSlot (lubricants_id, 2));
    machines2->AddInput(RecipeSlot (bearings_id, 2));
    machines2->AddInput(RecipeSlot (machines_id, 5, false));
    machines2->AddInput(RecipeSlot (energy_id, 45));
    machines2->AddOutput(RecipeSlot (machines_id, 2));
    AddRecipe(machines2);
    
    rapidxml::xml_document<> doc;
    auto node = doc.allocate_node(rapidxml::node_element, "xml");
    doc.insert_node(nullptr, node);
    
    for(auto& recipe : recipes_)
    {
        recipe->WriteInstance(node);
    }
    
    std::string xml_as_string;
    rapidxml::print(std::back_inserter(xml_as_string), doc);
    
    std::ofstream out("recipes.xml");
    out<<xml_as_string;
    out.close();
#endif
}

void World::AddTerritory(std::shared_ptr<Territory> territory)
{
    auto itr = territories_.find(territory->GetId());
    if(itr != territories_.end())
    {
        territories_.erase(itr);
    }
    territories_.insert(std::make_pair(territory->GetId(), territory));
    
    for(auto itr = territory->ResourcesBegin(); itr != territory->ResourcesEnd(); ++itr)
    {
        float qty = territory->GetResource(itr->first);
        total_resources_ += qty;
        global_static_resources_[itr->first] += qty;
    }
    
#if DEBUG && 0
    for(uint32_t res_id = resource_first; res_id<resource_count; ++res_id)
    {
        if(global_static_resources_[(ResourceId)res_id] == 0)
        {
            global_static_resource_scarcity_[(ResourceId)res_id] = -1.0f;
        }
        else
        {
            global_static_resource_scarcity_[(ResourceId)res_id] = (double)global_static_resources_[(ResourceId)res_id] / (double)total_resources_;
        }
    }
    
    printf("[World Static Resources]\n");
    for(uint32_t res_id = resource_first; res_id<resource_count; ++res_id)
    {
        printf("\t[Resource: %s %lu Scarcity: %f]\n", 
               ResourceNames[res_id], 
               global_static_resources_[(ResourceId)res_id],
               global_static_resource_scarcity_[(ResourceId)res_id]
        );
    }
#endif
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
    }
    return true;
}