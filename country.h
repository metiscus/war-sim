#pragma once

#include "factory.h"
#include <memory>
#include "serializer.h"
#include <set>
#include <string>
#include <vector>
#include "stockpile.h"

class World;

class Country : public ISerializer
{
public:
    typedef uint64_t Id;
    
private:
    std::shared_ptr<Stockpile> stockpile_;
    std::vector<Factory> factories_;
    std::set<uint32_t> territories_;
    std::string name_;
    Id id_;
    float dissent_;    
    RecipePtr FindRecipeForResource(ResourceId id);

public:
    Country();
    Country(Id id, const std::string& name);
    
    const std::string& GetName() const;
    Stockpile* GetStockpile();
    
    inline uint32_t GetId() const { return id_; }
    
    //TODO: Factories should be present in the territories
    void           AddFactory();
    void           RemoveFactory();
    uint32_t       GetFactoryCount() const;
    Factory*       GetFactory(uint32_t idx);
    //const Factory* GetFactory(uint32_t idx) const;
    
    void AddTerritory(uint32_t territory_id);
    void RemoveTerritory(uint32_t territory_id);
    const std::set<uint32_t>& GetTerritories() const;

    void GatherResources();
    void ProduceResources();
    void SimulateDomestic();
    
    bool ReadInstance(Node* node);
    bool WriteInstance(Node* node);
};