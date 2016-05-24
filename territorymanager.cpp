#include "territorymanager.h"
#include "territory.h"

#include <cassert>
#include <map>
#include <memory>
#include "rapidxml_utils.hpp"
#include <string>
#include <vector>

namespace TerritoryManager
{
    namespace {
        typedef std::shared_ptr<Territory> TerritoryPtr;
        std::vector<TerritoryPtr> territories_;
        std::map<std::string, uint32_t> territory_names_;
        std::map<TerritoryId, uint32_t> territory_ids_;
    }

    void LoadTerritoryFile(const std::string& filename)
    {
        // Load default recipes
        rapidxml::file<> file(filename.c_str());
        rapidxml::xml_document<> document;
        document.parse<0>(file.data());
        
        rapidxml::xml_node<> *node = document.first_node();
        if(node)
        {
            node = node->first_node();
        }

        while(node != nullptr)
        {
            TerritoryPtr territory = std::make_shared<Territory>();
            if(territory->ReadInstance(node))
            {
                territories_.emplace_back(territory);
                uint32_t index = territories_.size() - 1;
                territory_names_.insert(std::make_pair(territory->GetName(), index));
                territory_ids_.insert(std::make_pair(territory->GetId(), index));
            }
            else
            {
                assert(false);
            }
        }
    }
    
    Territory* GetTerritoryById(TerritoryId id)
    {
        std::map<TerritoryId, uint32_t>::const_iterator itr = territory_ids_.find(id);
        if(itr != territory_ids_.end())
        {
            return territories_.at(itr->second).get();
        }
        else
        {
            assert(false);
            return nullptr;
        }
    }
    
    Territory* GetTerritoryByName(const std::string& name)
    {
        std::map<std::string, uint32_t>::const_iterator itr = territory_names_.find(name);
        if(itr != territory_names_.end())
        {
            return territories_.at(itr->second).get();
        }
        else
        {
            assert(false);
            return nullptr;
        }
    }

    bool IsValidTerritoryId(TerritoryId id)
    {
        return territory_ids_.count(id) == 1;
    }
    
    bool IsValidTerritoryName(const std::string& name)
    {
        return territory_names_.count(name) == 1;
    }
}