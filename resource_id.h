#pragma once

#include <array>
#include <cstdint>
#include <string>

enum ResourceId
{
    resource_invalid,
    resource_first,
    resource_manpower = resource_first,
    resource_energy,
    resource_coal,
    resource_iron,
    resource_steel,
    resource_coke,
    resource_education,
    
    resource_count
};

extern const char* ResourceNames [];

class ResourceCount
{
    std::array<int64_t, resource_count> data_;
public:
    ResourceCount()
    {
        for(uint64_t i=0; i<resource_count; ++i)
        {
            data_[i] = 0;
        }
    }
    
    
    inline int64_t& operator[](uint64_t idx) { return data_[idx]; }
    inline const int64_t& operator[](uint64_t idx) const { return data_[idx]; }  
};