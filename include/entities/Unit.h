#pragma once

#include <string>

#include "entities/Entity.h"
#include "collision/CollisionShapeSquare.h"

class Unit : public Entity
{
public:
    std::string player = "";

    Vector velocity = {0, 0};

    bool selected = false;

    CollisionShapeSquare collisionShape = {{0, 0}, {32, 32}};

    Unit(std::string id, std::string player, Vector position);
    virtual ~Unit();

    void update(float dt) override;
    void output(SDL_Renderer *renderer, Camera *camera) override;

    void select();
    void deselect();
};