#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <set>

#include "serializer.h"

typedef uint64_t ResourceId;

class Resource : public ISerializer
{
private:
    std::string name_;
    std::string short_name_;
    ResourceId id_;
    double base_value_;
    
    static uint64_t s_resource_count_;
    static std::map<ResourceId, Resource> s_resources_;
    static std::map<std::string, ResourceId> s_resources_names_;
    static std::set<ResourceId> s_resource_ids_;
    
    friend class World;

protected:
    void SetName(const std::string& name);
    void SetShortName(const std::string& name);
    void SetId(ResourceId id);
    void SetBaseValue(double value);
    
    const std::string& GetName() const;
    const std::string& GetShortName() const;
    const ResourceId& GetId() const;
    const double& GetBaseValue() const;

    bool ReadInstance(rapidxml::xml_node<>* node);
    bool WriteInstance(rapidxml::xml_node<>* node);
    
public:
    Resource();

    static bool        LoadResourceFile(const std::string& name);
    static std::string GetResourceShortName(ResourceId id);
    static ResourceId  GetResourceByShortName(const std::string& name);
    static double      GetResourceBaseValue(ResourceId id);
    static ResourceId  GetFirstResourceId();
    static ResourceId  GetNextResourceId(ResourceId id);
};

template<typename Contained>
class ResourceContainer
{
protected:
    std::map<ResourceId, Contained> resources_;

public:
    inline Contained& operator[](ResourceId idx) 
    { 
        return resources_[idx]; 
    }

    inline const Contained operator[](ResourceId idx) const 
    { 
        auto itr = resources_.find(idx);
        if(itr != resources_.end())
        {
            return itr->second;
        }
        else
        {
            return Contained();
        }
    }
    
    inline bool Contains(ResourceId idx) const
    {
        return resources_.count(idx) > 0;
    }

    inline bool IsEmpty() const
    {
        for(auto slot : resources_)
        {
            if(slot.second != 0) return false;
        }
        return true;
    }
    
    typedef typename std::map<ResourceId, Contained>::const_iterator ConstIteratorType;
    typedef typename std::map<ResourceId, Contained>::iterator IteratorType;
        
    ConstIteratorType begin() const
    {
        return resources_.begin();
    }
    
    ConstIteratorType end() const
    {
        return resources_.end();
    }
    
    IteratorType begin()
    {
        return resources_.begin();
    }
    
    IteratorType end()
    {
        return resources_.end();
    }
    
};

template<typename CountType>
class ResourceCount
{
    ResourceContainer<CountType> resources_;

public:
    inline CountType& operator[](ResourceId idx)
    {
        if(!resources_.Contains(idx))
        {
            resources_[idx] = 0;
        }

        return resources_[idx];
    }
    
    inline CountType operator[](ResourceId idx) const
    {
        if(!resources_.Contains(idx))
        {
            return 0;
        }
        return resources_[idx];
    } 
    
    inline bool IsEmpty() const
    {
        return resources_.IsEmpty();
    }
    
    CountType ComputeTotal() const
    {
        uint32_t total = 0;
        for(auto slot : resources_)
        {
            total += slot.second;
        }
        return total;
    }
    
    ResourceId ComputeLargestType() const
    {
        CountType total = 0;
        ResourceId type = 0;
        for(auto slot : resources_)
        {
            if(slot.second >= total)
            {
                type  = (ResourceId)slot.first;
                total = slot.second;
            }
        }
        
        return type;
    }
    
    typedef typename ResourceContainer<CountType>::ConstIteratorType ConstIteratorType;
    ConstIteratorType begin() const
    {
        return resources_.begin();
    }
    
    ConstIteratorType end() const
    {
        return resources_.end();
    }
};