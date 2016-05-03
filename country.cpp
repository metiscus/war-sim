#include "country.h"
#include <cassert>
#include "stockpile.h"
#include "territory.h"
#include "world.h"


Country::Country(Id id, const std::string& name)
    : name_(name)
    , id_(id)
{
    stockpile_ = std::make_shared<Stockpile>();
}

const std::string& Country::GetName() const
{
    return name_;
}

std::shared_ptr<Stockpile> Country::GetStockpile()
{
    return stockpile_;
}

void Country::AddFactory()
{
    Factory f;
    f.SetStockpile(GetStockpile());
    factories_.push_back(f);
}

void Country::RemoveFactory()
{
    if(!factories_.empty())
    {
        factories_.resize(factories_.size() - 1);
    }
}
uint32_t Country::GetFactoryCount() const
{
    return factories_.size();
}

Factory& Country::GetFactory(uint32_t idx)
{
    assert(idx < factories_.size());
    return factories_[idx];
}

const Factory& Country::GetFactory(uint32_t idx) const
{
    assert(idx < factories_.size());
    return factories_[idx];
}

void Country::AddTerritory(uint32_t territory)
{
    territories_.insert(territory);
}

void Country::RemoveTerritory(uint32_t territory)
{
    territories_.erase(territory);
}

const std::set<uint32_t>& Country::GetTerritories() const
{
    return territories_;
}

RecipePtr Country::FindRecipeForResource(World* world, ResourceId id)
{
#if DEBUG
#define LOG(msg, ...)                                           \
    printf("%c[1;33m[Country::FindRecipeForResource] : ", 27);  \
    printf(msg, __VA_ARGS__);                                   \
    printf("%c[0m\n", 27);

#else
#define LOG(msg, ...)
#endif

    LOG("Asked to produce %s", ResourceNames[id]);
    // We want to produce some good and we have X factories
    auto target_recipes = world->GetRecipesForResource(id);   
    RecipePtr target_recipe;
    std::vector<ResourceCount> shortfalls;
    if(target_recipes.size() == 0)
    {
        printf("We have been asked to produce '%s' but there is not a way to produce that.\n",
               ResourceNames[id]);
        return target_recipe;
    }

    for(uint32_t ii=0; ii<target_recipes.size(); ++ii)
    {
        if(factories_[0].CanProduceRecipe(target_recipes[ii]))
        {
            LOG("Found a recipe '%s' to produce %s.", target_recipes[ii]->GetName().c_str(), ResourceNames[id]);
            return target_recipes[ii];
        }
        else 
        {
            LOG("Recipe '%s' to produce %s has a shortfall.", target_recipes[ii]->GetName().c_str(), ResourceNames[id]);
            shortfalls.push_back(factories_[0].ComputeResourceShortfall(target_recipes[ii]));
        }
    }
    
    // we were not able to find a recipe to produce the item directly, so find the
    // recipe with the fewest missing components and try to produce those instead
    uint32_t idx = 0;
    uint32_t least_shortfall = -1;
    ResourceId search_type = resource_invalid;
    for(uint32_t ii=0; ii<shortfalls.size(); ++ii)
    {
        uint32_t shortfall = shortfalls[ii].ComputeTotal();
        if(shortfall < least_shortfall)
        {
            search_type = shortfalls[idx].ComputeLargestType();
            if(search_type != id)
            {
                idx = ii;
                least_shortfall = shortfall;
            }
        }
    }
    
    if(search_type != id && search_type != resource_invalid)
    {
        // now with the least shortfall set, return a recipe to produce
        target_recipe = FindRecipeForResource(world, shortfalls[idx].ComputeLargestType());
    }
    return target_recipe;
#undef LOG
}

void Country::GatherResources(World* world)
{
    // get resources from our territories
    for(uint32_t territory_id : territories_)
    {
        auto territory = world->GetTerritory(territory_id);
        TerritoryResources resources = territory->GetResources();
        for(uint32_t res_id = resource_first; res_id<resource_count; ++res_id)
        {
            stockpile_->AddResource((ResourceId)res_id, (int64_t)resources.GetResource((ResourceId)res_id));
        }
    }
    
    // get what the factories made
    for(auto &factory: factories_)
    {
        factory.DeliverResources();
    }
    
    //TODO: plan what the factories should produce and set up for that
    
#if 0
    //HACK: this is just for testing
    auto energy_recipes = world->GetRecipesForResource(resource_energy);
    auto coke_recipes   = world->GetRecipesForResource(resource_coke);
    auto steel_recipes  = world->GetRecipesForResource(resource_steel);
    for(uint32_t ii=0; ii<factories_.size(); ++ii)
    {
        switch (ii%3)
        {
            case 0: factories_[ii].SetRecipe(energy_recipes[0]); break;
            case 1: factories_[ii].SetRecipe(coke_recipes[0]); break;
            case 2: factories_[ii].SetRecipe(steel_recipes[0]); break;
        }
    }
#else
    factories_[0].SetRecipe(FindRecipeForResource(world, resource_energy));
    factories_[1].SetRecipe(FindRecipeForResource(world, resource_fuel));
    factories_[2].SetRecipe(FindRecipeForResource(world, resource_steel));
    factories_[3].SetRecipe(FindRecipeForResource(world, resource_machines));
    
#endif
    
#if DEBUG
    printf("[Country: %s]\n", name_.c_str());
    stockpile_->Debug();
#endif
}

void Country::ProduceResources(World* world)
{
    // do stuff here
    for(auto &factory: factories_)
    {
        factory.GatherResources();
    }

    // do stuff here
    for(auto &factory: factories_)
    {
        factory.Produce();
    }
    
}