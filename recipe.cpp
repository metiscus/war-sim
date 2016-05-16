#include "recipe.h"
#include <cassert>

RecipeSlot::RecipeSlot()
    : resource_(0)
    , quantity_(0)
    , is_consumed_(false)
{
    ;
}

RecipeSlot::RecipeSlot(ResourceId id, int64_t quantity, bool is_consumed)
    : resource_(id)
    , quantity_(quantity)
    , is_consumed_(is_consumed)
{

}

ResourceId RecipeSlot::GetResourceId() const
{
    return resource_;
}

int64_t RecipeSlot::GetQuantity() const
{
    return quantity_;
}

bool RecipeSlot::GetIsConsumed() const
{
    return is_consumed_;
}

///////////////////////////////////////////////////////////////////////////////
uint64_t Recipe::NextId()
{
    static uint64_t id = 0;
    return ++id;
}

Recipe::Recipe(const std::string& name, uint64_t id)
    : name_(name)
    , id_(id)
{
    
}

void Recipe::AddInput(const RecipeSlot& input)
{
    inputs_.push_back(input);
    if(!input.GetIsConsumed())
    {
        outputs_.push_back(input);
    }
}

void Recipe::AddOutput(const RecipeSlot& output)
{
    outputs_.push_back(output);
}

void Recipe::SetInputs(const SlotList& inputs)
{
    inputs_ = inputs;
    for(auto input : inputs)
    {
        if(!input.GetIsConsumed())
        {
            outputs_.push_back(input);
        }
    }
}

void Recipe::SetOutputs(const SlotList& outputs)
{
    outputs_ = outputs;
    for(auto input : inputs_)
    {
        if(!input.GetIsConsumed())
        {
            outputs_.push_back(input);
        }
    }
}

const Recipe::SlotList& Recipe::GetInputs() const
{
    return inputs_;
}

const Recipe::SlotList& Recipe::GetOutputs() const
{
    return outputs_;
}

const std::string& Recipe::GetName() const
{
    return name_;
}

bool Recipe::IsValid() const
{
    return inputs_.size() > 0 && outputs_.size() > 0;
}

uint64_t Recipe::GetId() const
{
    return id_;
}

uint64_t Recipe::ComputeOutputQty(ResourceId id) const
{
    uint64_t output_qty = 0;
    for(auto output : outputs_)
    {
        if(output.GetResourceId() == id)
        {
            output_qty += output.GetQuantity();
        }
    }
    
    return output_qty;
}