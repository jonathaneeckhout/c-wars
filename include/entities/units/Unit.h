#pragma once

#include <string>

#include "entities/Entity.h"

class Unit : public Entity
{
    const int arrivalRadius = 10;

public:
    std::string player = "";
    const Vector size = {32, 32};
    Vector velocity = {0, 0};
    Vector targetPosition = {0, 0};
    float speed = 100.0f;

    Unit(std::string id, std::string player, Vector position);
    ~Unit();

    void update(float dt) override;
    void output(Renderer *renderer, Camera *camera) override;

    void select();
    void deselect();

    void move(Vector position);

private:
    void drawName(Renderer *renderer, Vector position, Vector offset);
    void drawPlayer(Renderer *renderer, Vector position, Vector offset);
};