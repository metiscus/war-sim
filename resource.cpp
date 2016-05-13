#include "resource.h"
#include <sstream>

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

void Resource::SetId(uint64_t id)
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

const uint64_t& Resource::GetId() const
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
        id_ = (uint64_t)ExtractIntegerAttribute(node, "id");
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