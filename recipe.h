#pragma once

#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp> 
#include <boost/archive/text_oarchive.hpp> 
#include <fstream>
#include <iostream>
#include "resource_id.h"
#include <string>
#include <vector>

class RecipeSlot
{
    friend class boost::serialization::access;
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
    
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        int64_t resource = resource_;
        archive & (resource);
        resource_ = (ResourceId)resource;
        archive & (quantity_);
        archive & (is_consumed_);
    }
};

class Recipe
{
    friend class boost::serialization::access;

public:
    typedef std::vector<RecipeSlot> RecipeSlotList;

private:
    RecipeSlotList inputs_;
    RecipeSlotList outputs_;
    std::string name_;

public:
    Recipe(const std::string& name);
    ~Recipe() = default;
    void AddInput(const RecipeSlot& input);
    void AddOutput(const RecipeSlot& output);
    void SetInputs(const RecipeSlotList& inputs);
    void SetOutputs(const RecipeSlotList& outputs);
    const RecipeSlotList& GetInputs() const;
    const RecipeSlotList& GetOutputs() const;
    const std::string& GetName() const;
    
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & (inputs_);
        archive & (outputs_);
        archive & (name_);
    }
};