#pragma once

#include <array>
#include <cstdint>
#include <string>

enum ResourceId
{
    resource_invalid,
    resource_first,
    resource_manpower = resource_first,
    resource_farmland,
    resource_foodstuffs,
    resource_energy,
    resource_coal,
    resource_rares,
    resource_crude,
    resource_iron,
    resource_tools,
    resource_steel,
    resource_coke,
    resource_lubricants,
    resource_fuel,
    resource_machines,
    resource_bearings,

    resource_count
};

extern const char* ResourceNames [];

class ResourceCount
{
    std::array<int64_t, resource_count> data_;
public:
    ResourceCount()
    {
        for(uint64_t ii=0; ii<resource_count; ++ii)
        {
            data_[ii] = 0;
        }
    }
    
    
    inline int64_t& operator[](uint64_t idx) { return data_[idx]; }
    inline const int64_t& operator[](uint64_t idx) const { return data_[idx]; }  
    inline bool IsEmpty() const
    {
        for(auto slot : data_)
        {
            if(slot != 0) return false;
        }
        return true;
    }
    
    uint32_t ComputeTotal() const
    {
        uint32_t total = 0;
        for(auto slot : data_)
        {
            total += slot;
        }
        return total;
    }
    
    ResourceId ComputeLargestType() const
    {
        ResourceId type = resource_invalid;
        uint32_t total = 0;
        for(uint64_t ii=0; ii<resource_count; ++ii)
        {
            if(data_[ii] >= total)
            {
                type = (ResourceId)ii;
                total = data_[ii];
            }
        }
        
        return type;
    }
};