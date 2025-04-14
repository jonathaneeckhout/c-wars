#pragma once
#include <string>
#include <SDL2/SDL.h>

#include "utils/Vector.h"
#include "Camera.h"
#include "collision/CollisionShape.h"

class Entity
{
public:
    SDL_Renderer *renderer;

    std::string id;
    std::string name;
    Vector position = {0, 0};

    CollisionShape *collisionShape = NULL;
    bool selected = false;

    Entity(std::string id, Vector position);

    virtual ~Entity();
    virtual void update(float dt) = 0;
    virtual void output(SDL_Renderer *renderer, Camera *camera) = 0;
};