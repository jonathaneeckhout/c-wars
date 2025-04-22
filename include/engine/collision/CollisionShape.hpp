#pragma once

#include "engine/Object.hpp"
#include "engine/Vector.hpp"

class CollisionShape : public Object
{
public:
    Vector position = {0, 0};

    CollisionShape(Vector position);
    virtual ~CollisionShape() = default;

    virtual bool collidesWith(const Vector &point) const = 0;
    virtual bool collidesWith(const CollisionShape &other) const = 0;
    virtual bool collidesWith(const class CollisionShapeSquare &square) const = 0;
};