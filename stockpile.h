#pragma once

#include "resource.h"
#include <cstdint>
#include <array>

class Stockpile
{
private:
    ResourceCount<int64_t> resources_;
    
public:
    Stockpile();
    bool ContainsResource(ResourceId id, int64_t qty) const;
    bool ContainsResources(const ResourceCount<uint64_t>& count) const;
    void AddResource(ResourceId id, int64_t qty);
    void GetResource(ResourceId id, int64_t qty);
    void GetResources(const ResourceCount<uint64_t>& count);
    int64_t GetResourceQuantity(ResourceId id) const;
  
    void Debug() const;
};