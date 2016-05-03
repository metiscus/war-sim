#include "factory.h"

#include <algorithm>
#include <cstdint>
#include "recipe.h"
#include "stockpile.h"


FactorySpecialization::FactorySpecialization()
{
    for(auto& slot : specialization_)
    {
        slot = 0.0f;
    }
}

float FactorySpecialization::GetSpecialization(ResourceId id)
{
    return specialization_[id];
}

void FactorySpecialization::RecordProduction(RecipePtr ptr)
{
    for(auto output : ptr->GetOutputs())
    {
        if(output.GetIsConsumed())
        {
            specialization_[output.GetResourceId()] += output.GetQuantity() / 10000.0f;
            
            specialization_[output.GetResourceId()] = std::min(1.0f, specialization_[output.GetResourceId()]);
        }
    }
}

void FactorySpecialization::Simulate()
{
    //TODO: tie this in to something else
    for(auto& slot : specialization_)
    {
        slot *= 0.9995;
    }
}

void FactorySpecialization::Debug() const
{
#ifdef DEBUG
    printf("\t[Factory Specialization]\n");
    for(uint32_t ii=resource_first; ii<resource_count; ++ii)
    {
        printf("\t\t[Resource: %s Specialization: %f]\n", ResourceNames[ii], specialization_[ii]);
    }
#endif
}

///////////////////////////////////////////////////////////////////////////////
Factory::Factory()
    : have_resources_(false)
    , modifier_(1.0)
{
    
}

void Factory::SetStockpile(std::shared_ptr<Stockpile> stockpile)
{
    stockpile_ = stockpile;
}

void Factory::SetRecipe(RecipePtr recipe)
{
    recipe_ = recipe;
}

void Factory::GatherResources()
{
    have_resources_ = false;

    if(stockpile_ && recipe_ && recipe_->IsValid())
    {
        // Build a list of required materials
        const Recipe::SlotList& input_slot_list = recipe_->GetInputs();
        ResourceCount input_resources;
        for(auto input_slot : input_slot_list)
        {
            input_resources[input_slot.GetResourceId()] += input_slot.GetQuantity();
        }
        
        // If we have the materials on hand, then run a production line
        if(stockpile_->ContainsResources(input_resources))
        {
            // Produce the good(s) by getting all inputs
            stockpile_->GetResources(input_resources);
            have_resources_ = true;
        }
    }        
}

void Factory::Produce(float modifier)
{
    modifier_ = modifier;

    if(have_resources_ && recipe_ && recipe_->IsValid())
    {
#if DEBUG

        printf("[Factory Produces %s]\n", recipe_->GetName().c_str());
#endif
    }
    
    specialization_.Simulate();
}

void Factory::DeliverResources()
{
    if(have_resources_ && stockpile_ && recipe_ && recipe_->IsValid())
    {
        // Deliver all outputs
        const Recipe::SlotList& output_slot_list = recipe_->GetOutputs();
        for(auto output_slot : output_slot_list)
        {
            if(output_slot.GetQuantity() > 0)
            {
                specialization_.RecordProduction(recipe_);
                
                if(output_slot.GetIsConsumed())
                {
                    // compute output bonus from specialization
                    float base_output = modifier_ * output_slot.GetQuantity();
                    float max_bonus_output = (float)base_output / 10.0f;
                    uint32_t output = base_output + max_bonus_output * specialization_.GetSpecialization(output_slot.GetResourceId());
                    stockpile_->AddResource(output_slot.GetResourceId(), output);
                }
                else
                {
                    stockpile_->AddResource(output_slot.GetResourceId(), output_slot.GetQuantity());
                }
            }
        }
    }
}

bool Factory::CanProduceRecipe(RecipePtr recipe) const
{
    assert(recipe);
    if(!recipe)
    {
        return false;
    }

    // Build a list of required materials
    const Recipe::SlotList& input_slot_list = recipe->GetInputs();
    ResourceCount input_resources;
    for(auto input_slot : input_slot_list)
    {
        input_resources[input_slot.GetResourceId()] += input_slot.GetQuantity();
    }

    return stockpile_->ContainsResources(input_resources);
}

ResourceCount Factory::ComputeResourceShortfall(RecipePtr recipe) const
{
    assert(recipe);
    
    if(!recipe)
    {
        ResourceCount missing_resources;
        missing_resources[0] = 1;
        return missing_resources;
    }

    // Build a list of missing materials
    const Recipe::SlotList& input_slot_list = recipe->GetInputs();
    ResourceCount missing_resources;
    for(auto input_slot : input_slot_list)
    {
        uint32_t on_hand_qty = stockpile_->GetResourceQuantity(input_slot.GetResourceId());
        if(on_hand_qty < input_slot.GetQuantity())
        {
            missing_resources[input_slot.GetResourceId()] = input_slot.GetQuantity() - on_hand_qty;
        }
    }

    return missing_resources;
}

void Factory::Debug() const
{
    specialization_.Debug();
}