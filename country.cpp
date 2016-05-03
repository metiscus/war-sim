#include "country.h"
#include <cassert>
#include "stockpile.h"
#include "territory.h"
#include "world.h"


Country::Country(Id id, const std::string& name)
    : name_(name)
    , id_(id)
    , dissent_(0.0f)
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
#if DEBUG && DEBUG_FIND_RECIPE
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

    RecipePtr candidate_recipe;
    uint32_t output_amount = 0;
    for(uint32_t ii=0; ii<target_recipes.size(); ++ii)
    {
        if(factories_[0].CanProduceRecipe(target_recipes[ii]))
        {
            LOG("Found a recipe '%s' to produce %s.", target_recipes[ii]->GetName().c_str(), ResourceNames[id]);
            uint64_t recipe_output = target_recipes[ii]->ComputeOutputQty(id);
            if(output_amount < recipe_output)
            {
                output_amount = recipe_output;
                candidate_recipe = target_recipes[ii];
            }
        }
        else 
        {
            LOG("Recipe '%s' to produce %s has a shortfall.", target_recipes[ii]->GetName().c_str(), ResourceNames[id]);
            shortfalls.push_back(factories_[0].ComputeResourceShortfall(target_recipes[ii]));
        }
    }
    
    if(candidate_recipe)
    {
        return candidate_recipe;
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
            if(resources.GetResourceIsProduced((ResourceId)res_id))
            {
                stockpile_->AddResource((ResourceId)res_id, (int64_t)resources.GetResource((ResourceId)res_id));
            }
        }
    }
    
    // get what the factories made
    for(auto &factory: factories_)
    {
        factory.DeliverResources();
    }
    
    //TODO: plan what the factories should produce and set up for that
    factories_[0].SetRecipe(FindRecipeForResource(world, resource_energy));
    factories_[1].SetRecipe(FindRecipeForResource(world, resource_crude));
    factories_[2].SetRecipe(FindRecipeForResource(world, resource_steel));
    //factories_[2].SetRecipe(FindRecipeForResource(world, resource_machines));
    //factories_[3].SetRecipe(FindRecipeForResource(world, resource_machines));
    for(uint32_t ii=3; ii<factories_.size(); ++ii)
    {
        factories_[ii].SetRecipe(FindRecipeForResource(world, resource_machines));
    }
    
#if DEBUG
    printf("[Country: %s]\n", name_.c_str());
    stockpile_->Debug();
#if DEBUG_FACTORY
    for(auto &factory: factories_)
    {
        factory.Debug();
    }
#endif
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
        factory.Produce(1.0f - dissent_);
    }
    
}

void Country::SimulateDomestic(World* world)
{
    // Each manpower that is in the pool will need 1 foodstuff per day to survive
    // when a foodstuf deficit exists, the population may decrease and dissent may increase
    uint32_t total_manpower = stockpile_->GetResourceQuantity(resource_manpower);
    uint32_t total_foodstuffs = stockpile_->GetResourceQuantity(resource_foodstuffs);
    if(total_foodstuffs < total_manpower)
    {
        dissent_ += 0.01f;
        
        if(total_foodstuffs < 0.9f * total_manpower)
        {
            dissent_ += 0.015f;
        }
        
        if(total_foodstuffs < 0.8f * total_manpower)
        {
            stockpile_->GetResource(resource_manpower, 0.01f * total_manpower);
            dissent_ += 0.055f;
        }
    }
    
    dissent_ = std::min(dissent_, 1.0f);
#if DEBUG
    printf("[Country::SimulateDomestic Dissent: %f]\n", dissent_);
#endif    
    stockpile_->GetResource(resource_foodstuffs, std::min(total_manpower, total_foodstuffs));
}