#pragma once

#include <fstream>
#include <iostream>
#include "resource.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

class RecipeSlot
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
};

class Recipe;
typedef std::shared_ptr<Recipe> RecipePtr;
class Recipe
{
public:
    typedef std::vector<RecipeSlot> SlotList;

private:
    SlotList inputs_;
    SlotList outputs_;
    std::string name_;
    uint64_t id_;
    
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        (void)version;
        archive & (inputs_);
        archive & (outputs_);
        archive & (name_);
    }

public:
    static uint64_t NextId();

    Recipe(const std::string& name = "invalid recipe", uint64_t id = NextId());
    ~Recipe() = default;
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
};