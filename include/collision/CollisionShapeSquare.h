#pragma once

#include "utils/Vector.h"
#include "collision/CollisionShape.h"

class CollisionShapeSquare : public CollisionShape
{
public:
    Vector size = {0, 0};

    CollisionShapeSquare(Vector position, Vector size);

    bool collidesWith(const CollisionShape &other) const override;
    bool collidesWith(const class CollisionShapeSquare &square) const override;
};