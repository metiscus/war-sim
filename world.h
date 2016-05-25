#pragma once

#include <cstdlib>
#include <cstring>

#include <map>
#include <memory>
#include <sstream>
#include <string>


#include "recipe.h"
#include "resource.h"
#include "serializer.h"
#include "country.h"
#include "territory.h"

#include <oolua.h>

class World;
class Country;
class Territory;

typedef std::weak_ptr<World> WorldWeakPtr;
typedef std::shared_ptr<World> WorldPtr;

enum PropertyType
{
    PropertyString,
    PropertyInteger,
    PropertyReal
};

class Property
{
    PropertyType type_;

    std::string string_;
    union {
        int64_t integer_;
        double real_;
    };
public:
    Property()
    {
        type_ = PropertyInteger;
        integer_ = 0;
    }

    inline void SetString(const std::string& str)
    {
        type_ = PropertyString;
        string_ = str;
    }
    
    inline void SetString(const char* string)
    {
        type_ = PropertyString;
        string_ = string;
    }
    
    inline void SetReal(double real)
    {
        type_ = PropertyReal;
        real_ = real;
    }
    
    inline void SetInteger(int64_t integer)
    {
        type_ = PropertyInteger;
        integer_ = integer;
    }
    
    int64_t GetInteger() const
    {
        if(type_ == PropertyInteger) return integer_;
        if(type_ == PropertyReal) return (int64_t)real_;
        if(type_ == PropertyString) return strtoll(string_.c_str(), nullptr, 10);
        return 0;
    }
    
    double GetReal() const
    {
        if(type_ == PropertyInteger) return (double)integer_;
        if(type_ == PropertyReal) return real_;
        if(type_ == PropertyString) return strtod(string_.c_str(), nullptr);
        return 0;
    }
    
    std::string GetString() const
    {
        if(type_ == PropertyInteger) 
        {
            std::stringstream ss;
            ss<<integer_;
            return ss.str();
        }
        if(type_ == PropertyReal)
        {
            std::stringstream ss;
            ss<<integer_;
            return ss.str();
        }
        if(type_ == PropertyString) return string_;
        return std::string("");
    }
        
};

class World : public ISerializer
{
private:
    static WorldPtr s_world_;
    std::map<uint64_t, Resource> resources_;
    
    std::map<uint32_t, std::shared_ptr<Country> > countries_;

    std::vector<RecipePtr> recipes_;
    std::multimap<ResourceId, RecipePtr> recipe_map_;

    std::map<std::string, Property> property_map_;
    
    std::shared_ptr<OOLUA::Script> lua_;
    
    World();
public:
    static void CreateDefaultWorld();
    static void LoadSavedWorld(const std::string& name);

    void AddTerritory(std::shared_ptr<Territory> territory);
    void AddCountry(std::shared_ptr<Country> country);
    Territory* GetTerritory(uint32_t id);
    Country* GetCountry(uint32_t id);   
    
    void AddRecipe(RecipePtr ptr);
    std::vector<RecipePtr> GetRecipesForResource(ResourceId id);
    
    void Simulate();
    
    virtual bool ReadInstance(ISerializer::Node* node);
    virtual bool WriteInstance(ISerializer::Node* node);
    
    
    static WorldWeakPtr GetWorld();
    static World*       GetWorldStrong();
    static int64_t      GetIntProperty(const char* name);
    static double       GetRealProperty(const char* name);
    static std::string  GetStringProperty(const char* name);
    static void         SetIntProperty(const char* name, int64_t value);
    static void         SetRealProperty(const char* name, double value);
    static void         SetStringProperty(const char* name, const char* value);
};