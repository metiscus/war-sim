#include "country.h"
#include <cassert>
#include "stockpile.h"
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

void Country::Simulate(World* world)
{
    // do stuff here
    
}