#include "resource.h"
#include <cassert>
#include <sstream>
#include "rapidxml_utils.hpp"

uint64_t Resource::s_resource_count_ = 0;
std::map<ResourceId, Resource> Resource::s_resources_;
std::map<std::string, ResourceId> Resource::s_resources_names_;

Resource::Resource()
    : name_("unnamed resource")
    , short_name_("unnamed_resource")
    , id_(0)
    , base_value_(0.)
{
    ;
}
    
void Resource::SetName(const std::string& name)
{
    name_ = name;
}

void Resource::SetShortName(const std::string& name)
{
    short_name_ = name;
}

void Resource::SetId(ResourceId id)
{
    id_ = id;
}

void Resource::SetBaseValue(double value)
{
    base_value_ = value;
}

const std::string& Resource::GetName() const
{
    return name_;
}

const std::string& Resource::GetShortName() const
{
    return short_name_;
}

const ResourceId& Resource::GetId() const
{
    return id_;
}

const double& Resource::GetBaseValue() const
{
    return base_value_;
}

bool Resource::ReadInstance(rapidxml::xml_node<>* node)
{
    if(node)
    {
        id_ = (ResourceId)ExtractIntegerAttribute(node, "id");
        name_ = ExtractStringAttribute(node, "name");
        short_name_ = ExtractStringAttribute(node, "short_name");
        base_value_ = ExtractRealAttribute(node, "base_value");
        return true;
    }
    return false;
}

bool Resource::WriteInstance(rapidxml::xml_node<>* node)
{
    bool success = true;
    using namespace rapidxml;
    if(node)
    {
        auto new_node = CreateChildNode(node, "resource");
        success = success && AppendIntegerAttribute(new_node, "id", id_);
        success = success && AppendStringAttribute(new_node, "name", name_);
        success = success && AppendStringAttribute(new_node, "short_name", short_name_);
        success = success && AppendRealAttribute(new_node, "base_value", base_value_);
    }
    else
    {
        success = false;
    }

    return success;
}

bool Resource::LoadResourceFile(const std::string& name)
{
    rapidxml::file<> f(name.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(f.data());
    auto node = doc.first_node();
    if(node) node = node->first_node();

    while(node != nullptr)
    {
        Resource r;
        if(r.ReadInstance(node))
        {
            s_resources_.insert(std::make_pair(r.GetId(), r));
            s_resources_names_.insert(std::make_pair(r.GetShortName(), r.GetId()));
            ++s_resource_count_;
            
            node = node->next_sibling();
        }
    }
}

std::string Resource::GetResourceName(ResourceId id)
{
    assert(s_resources_.count(id) > 0);
    
    auto itr = s_resources_.find(id);
    if(itr == s_resources_.end())
    {
        return "(invalid resource)";
    }
    else
    {
        return itr->second.GetName();
    }
}

ResourceId Resource::GetResourceByShortName(const std::string& name)
{
    assert(s_resources_names_.count(name) > 0);
    
    auto itr = s_resources_names_.find(name);
    if(itr == s_resources_names_.end())
    {
        return 0;
    }
    else
    {
        return itr->second;
    }
}

double Resource::GetResourceBaseValue(ResourceId id)
{
    assert(s_resources_.count(id) > 0);
    
    auto itr = s_resources_.find(id);
    if(itr == s_resources_.end())
    {
        return -1.0;
    }
    else
    {
        return itr->second.GetBaseValue();
    }
}