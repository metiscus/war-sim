#pragma once

#include <fstream>
#include <iostream>
#include "resource.h"
#include "serializer.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

#include <oolua.h>

class RecipeSlot : public ISerializer
{
private:
    ResourceId resource_;
    int64_t quantity_;
    bool is_consumed_;

public:
    RecipeSlot();
    ~RecipeSlot() = default;
    RecipeSlot(ResourceId id, int64_t quantity, bool is_consumed = true);
    
    ResourceId GetResourceId() const;
    int64_t GetQuantity() const;
    bool GetIsConsumed() const;
    
    virtual bool ReadInstance(Node* node);
    virtual bool WriteInstance(Node* node);
};

class Recipe;
typedef std::shared_ptr<Recipe> RecipePtr;
typedef std::vector<RecipeSlot> SlotList;
    
class Recipe : public ISerializer
{
private:
    SlotList inputs_;
    SlotList outputs_;
    std::string name_;
    uint64_t id_;
    uint64_t duration_;

public:
    static uint64_t NextId();

    Recipe(const std::string& name = "invalid recipe", uint64_t id = NextId());
    virtual ~Recipe() = default;
    void AddInput(const RecipeSlot& input);
    void AddOutput(const RecipeSlot& output);
    void SetInputs(const SlotList& inputs);
    void SetOutputs(const SlotList& outputs);
    void SetDuration(const uint64_t duration);
    const SlotList& GetInputs() const;
    const SlotList& GetOutputs() const;
    const std::string& GetName() const;
    uint64_t GetDuration() const;
    bool IsValid() const;
    uint64_t GetId() const;
    uint64_t ComputeOutputQty(ResourceId id) const;
    
    virtual bool ReadInstance(Node* node);
    virtual bool WriteInstance(Node* node);
};

#if 1
OOLUA_PROXY(SlotList)
    //OOLUA_MEM_FUNC(void, push_back, const RecipeSlot&)
    //OOLUA_MFUNC(pop_back)
    OOLUA_MFUNC_CONST(size)
OOLUA_PROXY_END
#else
OOLUA_PROXY(SlotList)
OOLUA_PROXY_END
#endif

OOLUA_PROXY(RecipeSlot)
    OOLUA_TAGS(
        No_public_constructors
    )

    OOLUA_CTORS(
        OOLUA_CTOR(uint64_t, int64_t, bool)
    )

    OOLUA_MFUNC_CONST(GetResourceId)    
    OOLUA_MFUNC_CONST(GetQuantity)
    OOLUA_MFUNC_CONST(GetIsConsumed)
OOLUA_PROXY_END



OOLUA_PROXY(Recipe)
    OOLUA_TAGS(
        No_public_constructors
    )

    OOLUA_CTORS(
        OOLUA_CTOR(const std::string&)
    )

    OOLUA_MFUNC_CONST(ComputeOutputQty)    
    OOLUA_MFUNC_CONST(GetName)
    OOLUA_MFUNC_CONST(GetInputs)
    OOLUA_MFUNC_CONST(GetOutputs)
    
//    OOLUA_MEM_FUNC(void, SetOwner, uint64_t)
//    OOLUA_MEM_FUNC(void, SetCore, uint64_t)
//    OOLUA_MEM_FUNC(void, SetResource, uint64_t, float, bool)
//    OOLUA_MEM_FUNC(void, ChangeResource, uint64_t, float)
OOLUA_PROXY_END