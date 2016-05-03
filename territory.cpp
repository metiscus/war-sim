#include "territory.h"

TerritoryResources::TerritoryResources()
{
    for(auto &resource: resources_)
    {
        resource = 0.f;
    }
}

void TerritoryResources::SetResource(ResourceId id, float qty)
{
    resources_[id] = qty;
}

float TerritoryResources::GetResource(ResourceId id) const
{
    return resources_[id];
}

void TerritoryResources::ChangeResource(ResourceId id, float qty)
{
    resources_[id] += qty;
}

///////////////////////////////////////////////////////////////////////////////
Territory::Territory(uint64_t id, const std::string& name, Country::Id owner)
    : name_(name)
    , id_(id)
    , owner_(owner)
    , core_(owner)
{
    
}

uint64_t Territory::GetId() const
{
    return id_;
}

const std::string& Territory::GetName() const
{
    return name_;
}

void Territory::SetOwner(Country::Id id)
{
    owner_ = id;
}

void Territory::SetCore(Country::Id id)
{
    core_ = id;
}

Country::Id Territory::GetOwner() const
{
    return owner_;
}

Country::Id Territory::GetCore() const
{
    return core_;
}

const TerritoryResources& Territory::GetResources() const
{
    return resources_;
}

TerritoryResources& Territory::GetResources()
{
    return resources_;
}

void Territory::SetResources(const TerritoryResources& resources)
{
    resources_ = resources;
}