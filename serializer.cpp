#include "serializer.h"
#include <cstdint>
#include <sstream>

ISerializer::Node* ISerializer::FindChildNode(Node* node, const std::string& name)
{
    if(!node) return nullptr;
    return node->first_node(name.c_str());
}

void ISerializer::ForAllChildren(Node* node, std::function<void(ISerializer::Node*)> functor)
{
    if(!node) return;
    Node *ptr = node->first_node();
    while(ptr != nullptr)
    {
        functor(ptr);
        ptr = node->next_sibling();
    }
}

ISerializer::Node* ISerializer::CreateChildNode(ISerializer::Node* node, const std::string& name)
{
    using namespace rapidxml;
    if(node)
    {
        xml_document<> *doc = node->document();
        if(!doc)
        {
            return nullptr;
        }
        
        auto new_node = doc->allocate_node(node_element, doc->allocate_string(name.c_str(), 0));
        node->append_node(new_node);
        
        return new_node;
    }
    return nullptr;
}

bool ISerializer::AppendIntegerAttribute(ISerializer::Node* node, const std::string& name, int64_t value)
{
    if(!node) return false;
    
    rapidxml::xml_document<> *doc = node->document();
    if(!doc) return false;
    
    std::stringstream ss;
    ss<<value;
    auto attribute = doc->allocate_attribute(
        doc->allocate_string(name.c_str(), 0), 
        doc->allocate_string(ss.str().c_str(), 0));
    node->append_attribute(attribute);
    return true;
}

bool ISerializer::AppendRealAttribute(ISerializer::Node* node, const std::string& name, double value)
{
    if(!node) return false;
    
    rapidxml::xml_document<> *doc = node->document();
    if(!doc) return false;
    
    std::stringstream ss;
    ss<<value;
    auto attribute = doc->allocate_attribute(
        doc->allocate_string(name.c_str(), 0), 
        doc->allocate_string(ss.str().c_str(), 0));

    node->append_attribute(attribute);
    return true;
}

bool ISerializer::AppendStringAttribute(ISerializer::Node* node, const std::string& name, const std::string& value)
{
    if(!node) return false;
    
    rapidxml::xml_document<> *doc = node->document();
    if(!doc) return false;

    auto attribute = doc->allocate_attribute(
        doc->allocate_string(name.c_str(), 0), 
        doc->allocate_string(value.c_str(), 0));
    node->append_attribute(attribute);
    return true;
}

int64_t ISerializer::ExtractIntegerAttribute(ISerializer::Node* node, const std::string& name)
{
    int64_t ret = 0;
    if(node)
    {
        rapidxml::xml_attribute<> *attribute = node->first_attribute(name.c_str(), 0, false);
        if(attribute && attribute->value())
        {
            std::stringstream ss;
            ss<<attribute->value();
            ss>>ret;
        }
    }

    return ret;
}

double ISerializer::ExtractRealAttribute(ISerializer::Node* node, const std::string& name)
{
    double ret = 0;
    if(node)
    {
        rapidxml::xml_attribute<> *attribute = node->first_attribute(name.c_str(), 0, false);
        if(attribute && attribute->value())
        {
            std::stringstream ss;
            ss<<attribute->value();
            ss>>ret;
        }
    }

    return ret;
}

std::string ISerializer::ExtractStringAttribute(ISerializer::Node* node, const std::string& name)
{
    std::string ret;
    if(node)
    {
        rapidxml::xml_attribute<> *attribute = node->first_attribute(name.c_str(), 0, false);
        if(attribute && attribute->value())
        {
            ret = attribute->value();
        }
    }

    return ret; 
}