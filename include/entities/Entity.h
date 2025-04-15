#pragma once
#include <string>

#include "utils/Vector.h"
#include "Renderer.h"
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

    const Vector size = {32, 32};
    const Vector selectedSize = {size.x + 2, size.y + 2};

    const Vector renderOffset = size / 2;
    const Vector selectedRenderOffset = (selectedSize - size) / 2;

    Entity(std::string id, Vector position);

    virtual ~Entity();
    virtual void update(float dt) = 0;
    virtual void output(Renderer *renderer, Camera *camera) = 0;
};