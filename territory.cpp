#include "territory.h"

TerritoryResources::TerritoryResources()
{
    for(auto &resource: resources_)
    {
        resource.quantity    = 0.f;
        resource.is_produced = false;
    }
}

void TerritoryResources::SetResource(ResourceId id, float qty, bool is_produced)
{
    resources_[id].quantity    = qty;
    resources_[id].is_produced = is_produced;
}

float TerritoryResources::GetResource(ResourceId id) const
{
    return resources_[id].quantity;
}

void TerritoryResources::ChangeResource(ResourceId id, float qty)
{
    resources_[id].quantity += qty;
}

bool TerritoryResources::GetResourceIsProduced(ResourceId id) const
{
    return resources_[id].is_produced;
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