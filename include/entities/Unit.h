#pragma once

#include <string>

#include "entities/Entity.h"

class Unit : public Entity
{
    const int arrivalRadius = 10;

public:
    std::string player = "";

    Vector velocity = {0, 0};

    Vector targetPosition = {0, 0};

    float speed = 100.0f;

    Unit(std::string id, std::string player, Vector position);
    virtual ~Unit();

    void update(float dt) override;
    void output(SDL_Renderer *renderer, Camera *camera) override;

    void select();
    void deselect();

    void move(Vector position);
};