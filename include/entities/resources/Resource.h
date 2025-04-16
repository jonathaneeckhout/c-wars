#pragma once

#include <string.h>

#include "entities/Entity.h"

class Resource : public Entity
{
public:
    const Vector size = {32, 32};

    Resource(std::string id, Map *map, Vector position);
    ~Resource();

    void update(float dt) override;
    void output(Renderer *renderer, Camera *camera) override;

    void drawName(Renderer *renderer, Vector position, Vector offset);
};