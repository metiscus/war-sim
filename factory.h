#pragma once

#include <array>
#include "resource_id.h"
#include "recipe.h"
#include <map>
#include <memory>

class Stockpile;

class FactorySpecialization
{
private:
    std::array<float, resource_count> specialization_;

public:
    FactorySpecialization();

    float GetSpecialization(ResourceId id);
    void RecordProduction(RecipePtr ptr);
    void Simulate();
    void Debug() const;
};

class Factory
{
private:
    std::shared_ptr<Stockpile> stockpile_;
    RecipePtr recipe_;
    bool have_resources_;
    FactorySpecialization specialization_;
    
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
    
    void Debug() const;
};