#pragma once

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <cassert>
#include <cstdint>
#include <functional>
#include <string>

class ISerializer
{
public:
    virtual ~ISerializer() = default;
    
    typedef rapidxml::xml_node<> Node;
    
    virtual bool ReadInstance(Node* node)  = 0;
    virtual bool WriteInstance(Node* node) = 0;
    
protected:
    Node* FindChildNode(Node* node, const std::string& name);
    void ForAllChildren(Node* node, std::function<void(ISerializer::Node*)> functor);
    Node* CreateChildNode(Node* node, const std::string& name);
    bool AppendIntegerAttribute (Node* node, const std::string& name, int64_t value);
    bool AppendRealAttribute    (Node* node, const std::string& name, double value);
    bool AppendStringAttribute  (Node* node, const std::string& name, const std::string& value);
    
    int64_t ExtractIntegerAttribute(Node* node, const std::string& name);
    double ExtractRealAttribute(Node* node, const std::string& name);
    std::string ExtractStringAttribute(Node* node, const std::string& name);

};