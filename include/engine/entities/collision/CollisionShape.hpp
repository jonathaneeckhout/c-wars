#pragma once

#include "engine/Vector.hpp"
#include "engine/entities/Entity.hpp"

class CollisionShape : public Entity
{
public:
    uint32_t layers = 0x000000001;

    CollisionShape(Vector position);
    virtual ~CollisionShape();

    virtual bool collidesWith(const Vector &point) const = 0;
    virtual bool collidesWith(const CollisionShape &other) const = 0;
    virtual bool collidesWith(const class CollisionShapeSquare &square) const = 0;
};