#include "stockpile.h"
#include <cassert>
#include <cstdio>
#include "resource_id.h"

Stockpile::Stockpile()
{
    for(uint64_t id=resource_first; id<resource_count; ++id)
    {
        resources_[id] = 0;
    }
}

bool Stockpile::ContainsResource(ResourceId id, int64_t qty) const
{
    assert(id>resource_first && resource_first<resource_count);
    return (resources_[id] >= qty);
}

bool Stockpile::ContainsResources(const ResourceCount& count) const
{
    for(uint64_t id=resource_first; id<resource_count; ++id)
    {
        if(resources_[id] < count[id]) return false;
    }

    return true;
}

void Stockpile::AddResource(ResourceId id, int64_t qty)
{
    assert(id>resource_first && resource_first<resource_count);
    resources_[id] += qty;
}

void Stockpile::GetResource(ResourceId id, int64_t qty)
{
    assert(id>resource_first && resource_first<resource_count);
    resources_[id] -= qty;
}

void Stockpile::GetResources(const ResourceCount& count)
{
    assert(ContainsResources(count));
    for(uint64_t id=resource_first; id<resource_count; ++id)
    {
        resources_[id] -= count[id];
    }
}

int64_t Stockpile::GetResourceQuantity(ResourceId id) const
{
    assert(id>resource_first && resource_first<resource_count);
    return resources_[id];
}


void Stockpile::Debug() const
{
#if DEBUG
    printf("[Stockpile (%p)]\n", this);
    for(uint64_t id=resource_first; id<resource_count; ++id)
    {
        printf("\t[Resource Id=%llu Qty=%lld]\n", id, resources_[id]);
    }
#endif
}
