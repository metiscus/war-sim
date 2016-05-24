#pragma once

#include <cstdint>
#include <string>

typedef uint32_t TerritoryId;
class Territory;

namespace TerritoryManager
{
    void LoadTerritoryFile(const std::string& filename);
    Territory* GetTerritoryById(TerritoryId id);
    Territory* GetTerritoryByName(const std::string& name);
    
    bool IsValidTerritoryId(TerritoryId id);
    bool IsValidTerritoryName(const std::string& name);
}