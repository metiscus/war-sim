#pragma once

#include "rapidxml.hpp"
#include <cstdint>
#include <string>

class ISerializer
{
public:
    virtual ~ISerializer() = default;
    virtual bool ReadInstance(rapidxml::xml_node<>* node)  = 0;
    virtual bool WriteInstance(rapidxml::xml_node<>* node) = 0;
    
protected:
    rapidxml::xml_attribute<>* AppendIntegerAttribute (rapidxml::xml_node<>* node, const std::string& name, int64_t value);
    rapidxml::xml_attribute<>* AppendRealAttribute    (rapidxml::xml_node<>* node, const std::string& name, double value);
    rapidxml::xml_attribute<>* AppendStringAttribute  (rapidxml::xml_node<>* node, const std::string& name, const std::string& value);
    
    int64_t ExtractIntegerAttribute(rapidxml::xml_node<>* node, const std::string& name);
    double ExtractRealAttribute(rapidxml::xml_node<>* node, const std::string& name);
    std::string ExtractStringAttribute(rapidxml::xml_node<>* node, const std::string& name);
};