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
    //HACK: for now we just hard code a few recipes in here
    std::vector<Recipe*> recipes;

    Recipe energy("energy from coal");
    energy.AddInput(RecipeSlot (resource_coal, 10));
    energy.AddInput(RecipeSlot (resource_manpower, 1, false));
    energy.AddOutput(RecipeSlot (resource_energy, 81));   
    recipes.push_back(&energy);
    
    Recipe coke("coke from energy and coal");
    coke.AddInput(RecipeSlot (resource_coal, 10));
    coke.AddInput(RecipeSlot (resource_energy, 1));
    coke.AddInput(RecipeSlot (resource_manpower, 1, false));
    coke.AddOutput(RecipeSlot (resource_coke, 1));
    recipes.push_back(&coke);
    
    Recipe steel("steel from coke, iron, and electricity");
    steel.AddInput(RecipeSlot (resource_manpower, 5, false));
    steel.AddInput(RecipeSlot (resource_energy, 100));
    steel.AddInput(RecipeSlot (resource_coke, 1));
    steel.AddInput(RecipeSlot (resource_iron, 10));
    steel.AddOutput(RecipeSlot (resource_steel, 8));
    recipes.push_back(&steel);

    for(uint32_t ii=0; ii<factories_.size(); ++ii)
    {
        factories_[ii].SetRecipe(*recipes[(ii % (recipes.size() + 1))]);
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