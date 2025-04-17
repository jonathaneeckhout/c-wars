#pragma once

#include <string>

#include "entities/Entity.h"

class Building : public Entity
{
public:
    std::string player = "";
    const Vector size = {32, 32};

    Building(std::string id, std::string player, Map *map, Vector position);
    ~Building();

    void update(float dt) override;
    void output(Renderer *renderer, Camera *camera) override;
};