#pragma once

#include <string.h>
#include <utility>

#include "entities/Entity.hpp"

class Resource : public Entity
{
public:
    std::string type = "Metal";
    float speed = 1.0f;

    const Vector size = {32, 32};

    Resource(std::string id, Map *map, Vector position);
    ~Resource();

    void update(float dt) override;
    void output(Renderer *renderer) override;

    std::pair<std::string, float> gather(float amount);
};