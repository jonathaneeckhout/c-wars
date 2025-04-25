#include "engine/entities/collision/CollisionShape.hpp"

CollisionShape::CollisionShape(Vector position) : Entity(position)
{
    name = "CollisionShape";
}

CollisionShape::~CollisionShape() {}