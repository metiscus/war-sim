#pragma once
#include <cstdint>
#include "node.h"
#include <vector>

namespace render
{
    class Group : public Node
    {
    private:
        std::vector<Node*> nodes_;
    
    public:
        Group();
        virtual ~Group();
        
        void AddChild(Node* node);
        void RemoveChild(Node* node);
        uint32_t GetNumChildren();
        const std::vector<Node*>& GetChildren() const;
        std::vector<Node*>& GetChildren();
        
        
        virtual void Accept(NodeVisitor& visitor);
    };
}