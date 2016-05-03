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