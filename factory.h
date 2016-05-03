#pragma once

#include "resource_id.h"
#include "recipe.h"
#include <map>
#include <memory>

class Stockpile;

class Factory
{
private:
    std::shared_ptr<Stockpile> stockpile_;
    RecipePtr recipe_;
    bool have_resources_;
    
public:
    Factory();
    ~Factory() = default;
    
    void SetStockpile(std::shared_ptr<Stockpile> stockpile);
    void SetRecipe(RecipePtr recipe);
    bool CanProduceRecipe(RecipePtr recipe) const;
    ResourceCount ComputeResourceShortfall(RecipePtr recipe) const;

    void GatherResources();
    void Produce();
    void DeliverResources();
};