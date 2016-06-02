#include "group.h"
#include <cassert>

namespace render 
{
    Group::Group()
    {
        
    }

    Group::~Group()
    {
        for(Node* ptr : nodes_)
        {
            delete ptr;
        }
        nodes_.clear();
    }

    void Group::AddChild(Node* node)
    {
        nodes_.push_back(node);
    }
    
    void Group::RemoveChild(Node* node)
    {
        assert(false);
        // unimplemented
    }
    
    uint32_t Group::GetNumChildren()
    {
        return nodes_.size();
    }
    
    const std::vector<Node*>& Group::GetChildren() const
    {
        return nodes_;
    }

    std::vector<Node*>& Group::GetChildren()
    {
        return nodes_;
    }
    
    void Group::Accept(NodeVisitor& visitor)
    {
        Node::Accept(visitor);
        for(Node* ptr : nodes_)
        {
            if(ptr)
            {
                ptr->Accept(visitor);
            }
        }
    }
}