#pragma once

#include <cstdint>
#include "resource.h"
#include "serializer.h"

#include <oolua.h>

class Stockpile : public ISerializer
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
    
    virtual bool ReadInstance(Node* node);
    virtual bool WriteInstance(Node* node);
};

OOLUA_PROXY(Stockpile)
    OOLUA_TAGS(
        No_default_constructor
    )
    
    OOLUA_MFUNC_CONST(ContainsResource)
    OOLUA_MFUNC(AddResource)
    OOLUA_MFUNC(GetResource)
    OOLUA_MFUNC_CONST(GetResourceQuantity)
    OOLUA_MFUNC_CONST(Debug)
OOLUA_PROXY_END