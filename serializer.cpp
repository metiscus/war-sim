#include "serializer.h"
#include <cstdint>
#include <sstream>

rapidxml::xml_attribute<>* ISerializer::AppendIntegerAttribute(rapidxml::xml_node<>* node, const std::string& name, int64_t value)
{
    if(!node) return nullptr;
    
    rapidxml::xml_document<> *doc = node->document();
    if(!doc) return nullptr;
    
    std::stringstream ss;
    ss<<value;
    node->append_attribute(doc->allocate_attribute(name.c_str(), ss.str().c_str()));
}

rapidxml::xml_attribute<>* ISerializer::AppendRealAttribute(rapidxml::xml_node<>* node, const std::string& name, double value)
{
    if(!node) return nullptr;
    
    rapidxml::xml_document<> *doc = node->document();
    if(!doc) return nullptr;
    
    std::stringstream ss;
    ss<<value;
    node->append_attribute(doc->allocate_attribute(name.c_str(), ss.str().c_str()));
}

rapidxml::xml_attribute<>* ISerializer::AppendStringAttribute(rapidxml::xml_node<>* node, const std::string& name, const std::string& value)
{
    if(!node) return nullptr;
    
    rapidxml::xml_document<> *doc = node->document();
    if(!doc) return nullptr;

    node->append_attribute(doc->allocate_attribute(name.c_str(), value.c_str()));
}

int64_t ISerializer::ExtractIntegerAttribute(rapidxml::xml_node<>* node, const std::string& name)
{
    int64_t ret = 0;
    if(node)
    {
        rapidxml::xml_attribute<> *attribute = node->first_attribute(name.c_str(), name.length(), false);
        if(attribute && attribute->value())
        {
            std::stringstream ss;
            ss<<attribute->value();
            ss>>ret;
        }
    }

    return ret;
}

double ISerializer::ExtractRealAttribute(rapidxml::xml_node<>* node, const std::string& name)
{
    double ret = 0;
    if(node)
    {
        rapidxml::xml_attribute<> *attribute = node->first_attribute(name.c_str(), name.length(), false);
        if(attribute && attribute->value())
        {
            std::stringstream ss;
            ss<<attribute->value();
            ss>>ret;
        }
    }

    return ret;
}

std::string ISerializer::ExtractStringAttribute(rapidxml::xml_node<>* node, const std::string& name)
{
    std::string ret;
    if(node)
    {
        rapidxml::xml_attribute<> *attribute = node->first_attribute(name.c_str(), name.length(), false);
        if(attribute && attribute->value())
        {
            ret = attribute->value();
        }
    }

    return ret; 
}