#include <iostream>

#include "collision/CollisionShapeSquare.hpp"

CollisionShapeSquare::CollisionShapeSquare(Vector position, Vector size) : CollisionShape(position), size(size) {}

bool CollisionShapeSquare::collidesWith(const Vector &point) const
{
    return point.x > position.x && point.x < position.x + size.x && point.y > position.y && point.y < position.y + size.y;
}

bool CollisionShapeSquare::collidesWith(const CollisionShape &other) const
{
    return other.collidesWith(*this);
}

bool CollisionShapeSquare::collidesWith(const CollisionShapeSquare &other) const
{
    return position.x + size.x > other.position.x &&
           position.x < other.position.x + other.size.x &&
           position.y + size.y > other.position.y &&
           position.y < other.position.y + other.size.y;
}