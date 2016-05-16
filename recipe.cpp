#include "recipe.h"
#include "resource.h"
#include <cassert>
#include <sstream>
#include <cstdio>

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

bool RecipeSlot::ReadInstance(Node* node)
{
    assert(node);
    if(node)
    {
        std::string resource_name = ExtractStringAttribute(node, "resource");
        std::stringstream ss;
        ss<<resource_name;
        ss>>resource_;
        if(!ss.good())
        {
            Resource::GetResourceByShortName(resource_name);
        }
        
        resource_    = 
        quantity_    = ExtractIntegerAttribute(node, "quantity");
        is_consumed_ = ExtractIntegerAttribute(node, "is_consumed") == 1;
        return true;
    }
    return false;
}

bool RecipeSlot::WriteInstance(Node* node)
{
    assert(node);
    bool success = true;
    using namespace rapidxml;
    if(node)
    {
        auto new_node = CreateChildNode(node, "slot");
        success = success && AppendIntegerAttribute(new_node, "quantity", quantity_);
        success = success && AppendStringAttribute(new_node, "resource", Resource::GetResourceShortName(resource_));
        success = success && AppendIntegerAttribute(new_node, "is_consumed", is_consumed_ ? 1 : 0);
    }
    else
    {
        success = false;
    }

    return success;
}
    
///////////////////////////////////////////////////////////////////////////////
uint64_t Recipe::NextId()
{
    static uint64_t id = 0;
    return ++id;
}

Recipe::Recipe(const std::string& name, uint64_t id)
    : ISerializer()
    , name_(name)
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

bool Recipe::ReadInstance(Node* node)
{
    assert(node);
    if(node)
    {
        id_    = ExtractIntegerAttribute(node, "id");
        name_  = ExtractStringAttribute(node, "name");
        
        Node *inputs = FindChildNode(node, "inputs");
        if(inputs) inputs = inputs->first_node();

        while(inputs != nullptr)
        {
            RecipeSlot slot;
            if(slot.ReadInstance(inputs))
            {
                inputs_.emplace_back(slot);
            }
            inputs = inputs->next_sibling();
        }
        
        Node *outputs = FindChildNode(node, "outputs");
        if(outputs) outputs = outputs->first_node();

        while(outputs != nullptr)
        {
            RecipeSlot slot;
            if(slot.ReadInstance(outputs))
            {
                outputs_.emplace_back(slot);
            }
            outputs = outputs->next_sibling();
        }
        return true;
    }
    return false;
}

bool Recipe::WriteInstance(Node* node)
{
    assert(node);
    bool success = true;
    using namespace rapidxml;
    if(node)
    {
        auto new_node = CreateChildNode(node, "recipe");
        success = success && AppendIntegerAttribute(new_node, "id", id_);
        success = success && AppendStringAttribute(new_node, "name", name_);
        auto outputs = CreateChildNode(new_node, "outputs");
        if(outputs)
        {
            for(auto slot : outputs_)
            {
                slot.WriteInstance(outputs);
            }
        }
        
        auto inputs = CreateChildNode(new_node, "inputs");
        if(inputs)
        {
            for(auto slot : inputs_)
            {
                slot.WriteInstance(inputs);
            }
        }
    }
    else
    {
        success = false;
    }

    return success;
}