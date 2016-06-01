#include "node.h"

namespace render 
{

Node::Node()
{
    layer_ = 0;
}

Transform& Node::GetTransform()
{
    return transform_;
}

void Node::SetTransform(const Transform& transform)
{
    transform_ = transform;
}

void Node::Translate(const Vector2& offset)
{
    transform_.Translate(offset);
}

void Node::SetPosition(const Vector2& position)
{
    transform_.SetPosition(position);
}

Vector2 Node::GetPosition() const
{
    return transform_.GetPosition();
}

void Node::Rotate(const float& offset)
{
    transform_.Rotate(offset);
}

void Node::SetRotation(const float& rotation)
{
    transform_.SetRotation(rotation);
}

float Node::GetRotation() const
{
    return transform_.GetRotation();
}

void Node::SetLayer(int layer)
{
    layer_ = layer;
}

int Node::GetLayer() const
{
    return layer_;
}

void Node::Accept(NodeVisitor& visitor)
{
    visitor.Visit(*this);
}
}