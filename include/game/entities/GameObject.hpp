#pragma once

#include "engine/entities/Entity.hpp"

class GameObject : public Entity
{
public:
    bool selected = false;

    GameObject(Vector position);

    virtual ~GameObject();
};