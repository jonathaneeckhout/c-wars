#pragma once
#include <string>
#include <SDL2/SDL.h>

#include "engine/Vector.hpp"
#include "engine/Object.hpp"

class Entity : public Object
{
public:
    Vector position;
    Vector velocity;

    Entity();

    Entity(Vector position);

    virtual ~Entity();
};