#pragma once

#include "resource_id.h"
#include "recipe.h"
#include <memory>

class Stockpile;

class Factory
{
private:
    std::shared_ptr<Stockpile> stockpile_;
    Recipe recipe_;
    bool have_resources_;
    
public:
    Factory();
    ~Factory() = default;
    
    void SetStockpile(std::shared_ptr<Stockpile> stockpile);
    void SetRecipe(const Recipe& recipe);

    void GatherResources();
    void Produce();
    void DeliverResources();
};