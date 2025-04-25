#pragma once

#include "engine/entities/Entity.hpp"
#include "engine/entities/collision/CollisionShape.hpp"

class GameObject : public Entity
{
public:
    bool selected = false;

    CollisionShape *selectionArea = nullptr;

    GameObject(Vector position);

    virtual ~GameObject();
};