#include "stockpile.h"
#include <cassert>
#include <cstdio>
#include "resource_id.h"

Stockpile::Stockpile()
{
    ;
}

bool Stockpile::ContainsResource(ResourceId id, int64_t qty) const
{
    return (resources_[id] >= qty);
}

bool Stockpile::ContainsResources(const ResourceCount<uint64_t>& count) const
{
    for(auto resource : count)
    {
        if(resources_[resource.first] < resource.second) return false;
    }

    return true;
}

void Stockpile::AddResource(ResourceId id, int64_t qty)
{
    resources_[id] += qty;
}

void Stockpile::GetResource(ResourceId id, int64_t qty)
{
    resources_[id] -= qty;
}

void Stockpile::GetResources(const ResourceCount<uint64_t>& count)
{
    assert(ContainsResources(count));
    for(auto& resource : count)
    {
        resources_[resource.first] -= resource.second;
    }
}

int64_t Stockpile::GetResourceQuantity(ResourceId id) const
{
    return resources_[id];
}


void Stockpile::Debug() const
{
#if DEBUG
    printf("[Stockpile (%p)]\n", this);
    for(auto resource : resources_)
    {
        printf("\t[Resource %s: Qty=%ld]\n", Resource::GetResourceShortName(resource.first).c_str(), resources_[resource.first]);
    }
#endif
}
