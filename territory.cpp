#include "territory.h"

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

void Territory::SetResource(ResourceId id, float qty, bool is_produced)
{
    resources_[id].quantity    = qty;
    resources_[id].is_produced = is_produced;
}

float Territory::GetResource(ResourceId id) const
{
    return resources_[id].quantity;
}

void Territory::ChangeResource(ResourceId id, float qty)
{
    resources_[id].quantity += qty;
}

bool Territory::GetResourceIsProduced(ResourceId id) const
{
    return resources_[id].is_produced;
}

Territory::ResourceIteratorType Territory::ResourcesBegin() const
{
    return resources_.begin();
}

Territory::ResourceIteratorType Territory::ResourcesEnd() const
{
    return resources_.end();
}