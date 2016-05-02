#include "world.h"

World::World()
{
    
}

void World::AddTerritory(std::shared_ptr<Territory> territory)
{
    auto itr = territories_.find(territory->GetId());
    if(itr != territories_.end())
    {
        territories_.erase(itr);

    }
    territories_.insert(std::make_pair(territory->GetId(), territory));
}

void World::AddCountry(std::shared_ptr<Country> country)
{
    auto itr = countries_.find(country->GetId());
    if(itr != countries_.end())
    {
        countries_.erase(itr);
    }
    countries_.insert(std::make_pair(country->GetId(), country));
    
}

std::shared_ptr<Territory> World::GetTerritory(uint32_t id)
{
    std::shared_ptr<Territory> ret;
    auto itr = territories_.find(id);
    if(itr != territories_.end())
    {
        ret = itr->second;
    }
    return ret;
}

std::shared_ptr<Country> World::GetCountry(uint32_t id)
{
    std::shared_ptr<Country> ret;
    auto itr = countries_.find(id);
    if(itr != countries_.end())
    {
        ret = itr->second;
    }
    return ret;
}

void World::Simulate()
{
    // do stuff 
    for(auto country : countries_)
    {
        country.second->GatherResources(this);
    }
    
    for(auto country : countries_)
    {
        country.second->ProduceResources(this);
    }
}