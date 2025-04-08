#pragma once
#include <SDL2/SDL.h>

#include "utils/Vector.h"
#include "Camera.h"

class Entity
{
public:
    SDL_Renderer *renderer;

    Vector position = {0, 0};
    Vector velocity = {0, 0};

    Entity(Vector position);

    virtual ~Entity();
    virtual void update(float dt) = 0;
    virtual void output(SDL_Renderer *renderer, Camera *camera) = 0;
};