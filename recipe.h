#pragma once

#include <fstream>
#include <iostream>
#include "resource.h"
#include "serializer.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

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
class Recipe : public ISerializer
{
public:
    typedef std::vector<RecipeSlot> SlotList;

private:
    SlotList inputs_;
    SlotList outputs_;
    std::string name_;
    uint64_t id_;

public:
    static uint64_t NextId();

    Recipe(const std::string& name = "invalid recipe", uint64_t id = NextId());
    virtual ~Recipe() = default;
    void AddInput(const RecipeSlot& input);
    void AddOutput(const RecipeSlot& output);
    void SetInputs(const SlotList& inputs);
    void SetOutputs(const SlotList& outputs);
    const SlotList& GetInputs() const;
    const SlotList& GetOutputs() const;
    const std::string& GetName() const;
    bool IsValid() const;
    uint64_t GetId() const;
    uint64_t ComputeOutputQty(ResourceId id) const;
    
    virtual bool ReadInstance(Node* node);
    virtual bool WriteInstance(Node* node);
};