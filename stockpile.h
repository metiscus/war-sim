#pragma once

#include "resource_id.h"
#include <cstdint>
#include <array>

class Stockpile
{
private:
    typedef std::array<int64_t, resource_count> ResourceStockpile;
    ResourceStockpile resources_;
    
public:
    Stockpile();
    bool ContainsResource(ResourceId id, int64_t qty) const;
    void AddResource(ResourceId id, int64_t qty);
    void GetResource(ResourceId id, int64_t qty);
    int64_t GetResourceQuantity(ResourceId id) const;
};