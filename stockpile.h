#pragma once

#include <boost/archive/text_iarchive.hpp> 
#include <boost/archive/text_oarchive.hpp> 

#include "resource_id.h"
#include <cstdint>
#include <array>

class Stockpile
{
    friend class boost::serialization::access;

private:
    ResourceCount resources_;
    
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        (void)version;
        archive & (resources_);
    }
    
public:
    Stockpile();
    bool ContainsResource(ResourceId id, int64_t qty) const;
    bool ContainsResources(const ResourceCount& count) const;
    void AddResource(ResourceId id, int64_t qty);
    void GetResource(ResourceId id, int64_t qty);
    void GetResources(const ResourceCount& count);
    int64_t GetResourceQuantity(ResourceId id) const;
  
    void Debug() const;
};