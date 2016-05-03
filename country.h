#pragma once

#include <boost/archive/text_iarchive.hpp> 
#include <boost/archive/text_oarchive.hpp> 

#include "factory.h"
#include <memory>
#include <string>
#include <vector>
#include <set>

class Stockpile;
class World;

class Country
{
    friend class boost::serialization::access;
public:
    typedef uint64_t Id;
    
private:
    std::shared_ptr<Stockpile> stockpile_;
    std::vector<Factory> factories_;
    std::set<uint32_t> territories_;
    std::string name_;
    Id id_;
    float dissent_;

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        (void)version;
        archive & (stockpile_);
        archive & (factories_);
        archive & (territories_);
        archive & (name_);
        archive & (id_);
    }    
    
    
    RecipePtr FindRecipeForResource(World* world, ResourceId id);

public:
    Country(Id id, const std::string& name);
    
    const std::string& GetName() const;
    std::shared_ptr<Stockpile> GetStockpile();
    
    inline uint32_t GetId() const { return id_; }
    
    void AddFactory();
    void RemoveFactory();
    uint32_t GetFactoryCount() const;
    Factory& GetFactory(uint32_t idx);
    const Factory& GetFactory(uint32_t idx) const;
    
    void AddTerritory(uint32_t territory);
    void RemoveTerritory(uint32_t territory);
    const std::set<uint32_t>& GetTerritories() const;

    void GatherResources(World* world);
    void ProduceResources(World* world);
    void SimulateDomestic(World* world);
};
