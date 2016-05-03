#pragma once

#include <boost/archive/text_iarchive.hpp> 
#include <boost/archive/text_oarchive.hpp> 

#include <array>
#include <cstdint>
#include <string>
#include "country.h"

#include "resource_id.h"

class TerritoryResources
{
    friend class boost::serialization::access;
private:
    struct ResourceInfo
    {
        friend class boost::serialization::access;
        
        float quantity;
        bool  is_produced;
        
        template<class Archive>
        void serialize(Archive& archive, const unsigned int version)
        {
            (void)version;
            archive & (quantity);
            archive & (is_produced);
        }
    };

    std::array<ResourceInfo, resource_count> resources_;
    
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        (void)version;
        archive & (resources_);
    }
    
public:
    TerritoryResources();
    void SetResource(ResourceId id, float qty, bool is_produced = true);
    void ChangeResource(ResourceId id, float qty);
    float GetResource(ResourceId id) const;
    bool GetResourceIsProduced(ResourceId id) const;

};

class Territory
{
    friend class boost::serialization::access;
private:
    std::string name_;
    uint64_t id_;
    Country::Id owner_;
    Country::Id core_;
    
    TerritoryResources resources_;
    
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        (void)version;
        archive & (name_);
        archive & (id_);
        archive & (owner_);
        archive & (core_);
        archive & (resources_);
    }
    

public:
    Territory(uint64_t id, const std::string& name, Country::Id owner);
    
    uint64_t GetId() const;
    const std::string& GetName() const;
    
    void SetOwner(Country::Id id);
    void SetCore(Country::Id id);
    
    Country::Id GetOwner() const;
    Country::Id GetCore() const;

    const TerritoryResources& GetResources() const;
    TerritoryResources& GetResources();
    void SetResources(const TerritoryResources& resources);
};