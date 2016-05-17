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

bool Stockpile::ReadInstance(Node* node)
{
    assert(node);
    if(node)
    {
        node = node->first_node("resource");
        while(node)
        {
            ResourceId id = Resource::GetResourceByShortName(ExtractStringAttribute(node, "id"));
            uint64_t qty = ExtractIntegerAttribute(node, "qty");
            resources_[id] = qty;
            
            node = node->next_sibling();
        }
        return true;
    }
    return false;
}

bool Stockpile::WriteInstance(Node* node)
{
    assert(node);
    auto my_node = CreateChildNode(node, "stockpile");
    if(my_node)
    {
        for(auto resource : resources_)
        {
            auto res_node = CreateChildNode(my_node, "resource");
            AppendStringAttribute(res_node, "id", Resource::GetResourceShortName(resource.first));
            AppendIntegerAttribute(res_node, "qty", resource.second);
        }
        return true;
    }
    return false;
}