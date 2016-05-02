#include "factory.h"

#include "recipe.h"
#include "stockpile.h"

Factory::Factory()
{
    
}

void Factory::SetStockpile(std::shared_ptr<Stockpile> stockpile)
{
    stockpile_ = stockpile;
}

void Factory::SetRecipe(const Recipe& recipe)
{
    recipe_ = recipe;
}

void Factory::Simulate()
{
    if(stockpile_ && recipe_.IsValid())
    {
        // Build a list of required materials
        const Recipe::SlotList& input_slot_list = recipe_.GetInputs();
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
            
            // Then delivering all outputs
            const Recipe::SlotList& output_slot_list = recipe_.GetOutputs();
            for(auto output_slot : output_slot_list)
            {
                if(output_slot.GetQuantity() > 0)
                {
                    stockpile_->AddResource(output_slot.GetResourceId(), output_slot.GetQuantity());
                }
            }
        }
    }        
}