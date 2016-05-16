#pragma once

#include <array>
#include <cstdint>
#include <string>
#include "country.h"

#include "resource_id.h"

class Territory
{
private:
    std::string name_;
    uint64_t id_;
    Country::Id owner_;
    Country::Id core_;
    
    struct ResourceInfo
    {
        float quantity;
        bool  is_produced;
    };
    
    ResourceContainer<ResourceInfo> resources_;    

public:
    Territory(uint64_t id, const std::string& name, Country::Id owner);
    
    uint64_t GetId() const;
    const std::string& GetName() const;
    
    void SetOwner(Country::Id id);
    void SetCore(Country::Id id);
    
    Country::Id GetOwner() const;
    Country::Id GetCore() const;
    
    void  SetResource(ResourceId id, float qty, bool is_produced = true);
    void  ChangeResource(ResourceId id, float qty);
    float GetResource(ResourceId id) const;
    bool  GetResourceIsProduced(ResourceId id) const;
    
    typedef ResourceContainer<ResourceInfo>::ConstIteratorType ResourceIteratorType;
    ResourceIteratorType ResourcesBegin() const;
    ResourceIteratorType ResourcesEnd() const;
};