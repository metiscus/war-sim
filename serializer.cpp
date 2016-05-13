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

ISerializer::Node* ISerializer::CreateChildNode(ISerializer::Node* node, const std::__cxx11::string& name)
{
    using namespace rapidxml;
    if(node)
    {
        xml_document<> *doc = node->document();
        if(!doc)
        {
            return nullptr;
        }
        
        auto new_node = doc->allocate_node(node_element, name.c_str());
        node->append_node(new_node);
        
        return new_node;
    }
    return nullptr;
}

bool ISerializer::AppendIntegerAttribute(ISerializer::Node* node, const std::__cxx11::string& name, int64_t value)
{
    if(!node) return false;
    
    rapidxml::xml_document<> *doc = node->document();
    if(!doc) return false;
    
    std::stringstream ss;
    ss<<value;
    node->append_attribute(doc->allocate_attribute(name.c_str(), ss.str().c_str()));
    return true;
}

bool ISerializer::AppendRealAttribute(ISerializer::Node* node, const std::__cxx11::string& name, double value)
{
    if(!node) return false;
    
    rapidxml::xml_document<> *doc = node->document();
    if(!doc) return false;
    
    std::stringstream ss;
    ss<<value;
    node->append_attribute(doc->allocate_attribute(name.c_str(), ss.str().c_str()));
    return true;
}

bool ISerializer::AppendStringAttribute(ISerializer::Node* node, const std::string& name, const std::string& value)
{
    if(!node) return false;
    
    rapidxml::xml_document<> *doc = node->document();
    if(!doc) return false;

    node->append_attribute(doc->allocate_attribute(name.c_str(), value.c_str()));
    return true;
}

int64_t ISerializer::ExtractIntegerAttribute(ISerializer::Node* node, const std::string& name)
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

double ISerializer::ExtractRealAttribute(ISerializer::Node* node, const std::string& name)
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

std::string ISerializer::ExtractStringAttribute(ISerializer::Node* node, const std::string& name)
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