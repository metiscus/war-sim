#include "recipe.h"
#include <cassert>

RecipeSlot::RecipeSlot()
    : resource_(resource_invalid)
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

///////////////////////////////////////////////////////////////////////////////


Recipe::Recipe(const std::string& name)
    : name_(name)
{
    
}

void Recipe::AddInput(const RecipeSlot& input)
{
    inputs_.push_back(input);
}

void Recipe::AddOutput(const RecipeSlot& output)
{
    outputs_.push_back(output);
}

void Recipe::SetInputs(const RecipeSlotList& inputs)
{
    inputs_ = inputs;
}

void Recipe::SetOutputs(const RecipeSlotList& outputs)
{
    outputs_ = outputs;
}

const Recipe::RecipeSlotList& Recipe::GetInputs() const
{
    return inputs_;
}

const Recipe::RecipeSlotList& Recipe::GetOutputs() const
{
    return outputs_;
}

const std::string& Recipe::GetName() const
{
    return name_;
}