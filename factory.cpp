#include "factory.h"

#include "recipe.h"
#include "stockpile.h"

Factory::Factory()
    : have_resources_(false)
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

void Factory::Produce()
{
#if DEBUG
    if(have_resources_ && recipe_ && recipe_->IsValid())
    {
        printf("[Factory Produces %s]\n", recipe_->GetName().c_str());
    }
#endif
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
                stockpile_->AddResource(output_slot.GetResourceId(), output_slot.GetQuantity());
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