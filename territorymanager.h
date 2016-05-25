#pragma once

#include <cstdint>
#include <memory>
#include <string>

typedef uint32_t TerritoryId;
class Territory;

namespace TerritoryManager
{
    void Reset();
    void LoadTerritoryFile(const std::string& filename);
    void WriteTerritoryFile(const std::string& filename);
    
    void AddTerritory(std::shared_ptr<Territory> territory);
    const Territory* GetTerritoryById(TerritoryId id);
    Territory* GetTerritoryByIdRw(TerritoryId id);
    const Territory* GetTerritoryByName(const std::string& name);
    Territory* GetTerritoryByNameRw(const std::string& name);
    
    bool IsValidTerritoryId(TerritoryId id);
    bool IsValidTerritoryName(const std::string& name);
}