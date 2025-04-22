#pragma once

#include "engine/collision/CollisionShape.hpp"

class CollisionShapeSquare : public CollisionShape
{
public:
    Vector size = {0, 0};

    CollisionShapeSquare(Vector position, Vector size);

    bool collidesWith(const Vector &position) const override;
    bool collidesWith(const CollisionShape &other) const override;
    bool collidesWith(const class CollisionShapeSquare &square) const override;
};