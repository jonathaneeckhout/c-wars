#pragma once

#include <SDL2/SDL.h>

#include "engine/entities/Entity.hpp"

class UI : public Entity
{
public:
    UI(Vector position);
    ~UI() override;
};