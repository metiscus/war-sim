#pragma once

#include <boost/archive/text_iarchive.hpp> 
#include <boost/archive/text_oarchive.hpp> 

#include <map>
#include <memory>

#include "country.h"
#include "territory.h"


class World
{
    friend class boost::serialization::access;
private:
    
    std::map<uint32_t, std::shared_ptr<Territory> > territories_;
    std::map<uint32_t, std::shared_ptr<Country> > countries_;

public:
    World();

    void AddTerritory(std::shared_ptr<Territory> territory);
    void AddCountry(std::shared_ptr<Country> country);
    std::shared_ptr<Territory> GetTerritory(uint32_t id);
    std::shared_ptr<Country> GetCountry(uint32_t id);   
    
    void Simulate();
    
};