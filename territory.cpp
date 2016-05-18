#include "territory.h"

OOLUA_EXPORT_FUNCTIONS(Territory
    ,SetOwner
    ,ChangeResource
)

OOLUA_EXPORT_FUNCTIONS_CONST(Territory
    ,GetOwner
    ,GetResource
    ,GetResourceIsProduced
)


bool Territory::ResourceInfo::ReadInstance(ISerializer::Node* node)
{
    assert(node);
    if(node)
    {
        id = Resource::GetResourceByShortName(ExtractStringAttribute(node, "id"));
        quantity = ExtractRealAttribute(node, "quantity");
        is_produced = ExtractIntegerAttribute(node, "is_produced") == 1;
        return true;
    }
    return false;
}

bool Territory::ResourceInfo::WriteInstance(ISerializer::Node* node)
{
    assert(node);
    if(node)
    {
        Node* slot = CreateChildNode(node, "resource");
        AppendStringAttribute(slot, "id", Resource::GetResourceShortName(id));
        AppendRealAttribute(slot, "quantity", quantity);
        AppendIntegerAttribute(slot, "is_produced", is_produced ? 1 : 0);
        return true;
    }
    return false;
}

Territory::Territory()
    : name_("invalid")
    , id_(0)
    , owner_(0)
    , core_(0)
{
    fprintf(stderr,"%p territory constructor!\n", this);
}

Territory::Territory(uint64_t id, const std::string& name, Country::Id owner)
    : name_(name)
    , id_(id)
    , owner_(owner)
    , core_(owner)
{
}

uint64_t Territory::GetId() const
{
    return id_;
}

const std::string& Territory::GetName() const
{
    return name_;
}

void Territory::SetOwner(Country::Id id)
{
    owner_ = id;
}

void Territory::SetCore(Country::Id id)
{
    core_ = id;
}

Country::Id Territory::GetOwner() const
{
    return owner_;
}

Country::Id Territory::GetCore() const
{
    return core_;
}

void Territory::SetResource(ResourceId id, float qty, bool is_produced)
{
    resources_[id].id = id;
    resources_[id].quantity    = qty;
    resources_[id].is_produced = is_produced;
}

float Territory::GetResource(ResourceId id) const
{
    return resources_[id].quantity;
}

void Territory::ChangeResource(ResourceId id, float qty)
{
    resources_[id].quantity += qty;
}

bool Territory::GetResourceIsProduced(ResourceId id) const
{
    return resources_[id].is_produced;
}

Territory::ResourceIteratorType Territory::ResourcesBegin() const
{
    return resources_.begin();
}

Territory::ResourceIteratorType Territory::ResourcesEnd() const
{
    return resources_.end();
}

bool Territory::ReadInstance(ISerializer::Node* node)
{
    assert(node);
    if(node)
    {
        id_ = ExtractIntegerAttribute(node, "id");
        owner_ = ExtractIntegerAttribute(node, "owner");
        core_ = ExtractIntegerAttribute(node, "core");
        name_ = ExtractStringAttribute(node, "name");
        
        Node *resources = FindChildNode(node, "resources");
        if(resources)
        {
            ForAllChildren(resources, [this] (ISerializer::Node* node) {
                ResourceInfo info;
                if(info.ReadInstance(node))
                {
#if 0
                    printf("Resource: %s Qty: %f IsProduced: %s\n", 
                           Resource::GetResourceShortName(info.id).c_str(), 
                           info.quantity,
                           info.is_produced ? "true" : "false"
                    );
#endif
                    resources_[info.id] = info;
                }
            });
            return true;
        }
    }
    return false;
}

bool Territory::WriteInstance(ISerializer::Node* node)
{
    assert(node);
    if(node)
    {
        Node* territory = CreateChildNode(node, "territory");
        AppendIntegerAttribute(territory, "id", id_);
        AppendStringAttribute(territory, "name", name_);
        AppendIntegerAttribute(territory, "owner", owner_);
        AppendIntegerAttribute(territory, "core", core_);
        
        Node* resources = CreateChildNode(territory, "resources");
        for(auto resource : resources_)
        {
            resource.second.WriteInstance(resources);
        }
    }
    return false;
}