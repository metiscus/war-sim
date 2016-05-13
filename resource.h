#pragma once

#include <cstdint>
#include <string>

#include "serializer.h"


class Resource : public ISerializer
{
private:
    std::string name_;
    std::string short_name_;
    uint64_t id_;
    double base_value_;
    
public:
    Resource();
    
    void SetName(const std::string& name);
    void SetShortName(const std::string& name);
    void SetId(uint64_t id);
    void SetBaseValue(double value);
    
    const std::string& GetName() const;
    const std::string& GetShortName() const;
    const uint64_t& GetId() const;
    const double& GetBaseValue() const;
    
    bool ReadInstance(rapidxml::xml_node<>* node);
    bool WriteInstance(rapidxml::xml_node<>* node);
};