#pragma once

#include "transform.h"
#include "vector.h"

class Node;
class NodeVisitor
{
public:
    virtual ~NodeVisitor() = default;
    virtual void Visit(Node& node) = 0;
};

class Node
{
private:
    Transform transform_;
    int layer_;

public:
    Node();
    virtual ~Node() = default;

    Transform& GetTransform();
    void SetTransform(const Transform& transform);

    void Translate(const Vector2& offset);
    void SetPosition(const Vector2& position);
    Vector2 GetPosition() const;
    
    void Rotate(const float& offset);
    void SetRotation(const float& rotation);
    float GetRotation() const;
    
    void SetLayer(int layer);
    int GetLayer() const;
    
    virtual void Accept(NodeVisitor& visitor);
};