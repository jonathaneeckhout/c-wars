#pragma once

#include <string>
#include <utility>

#include "entities/Entity.hpp"

class Building : public Entity
{
public:
    std::string player = "";
    const Vector size = {32, 32};

    bool storage = false;

    Building(std::string id, std::string player, Map *map, Vector position);
    ~Building();

    void update(float dt) override;
    void output(Renderer *renderer) override;

    void store(std::pair<std::string, float> goods);

private:
    void drawPlayer(Renderer *renderer, Vector position, Vector offset);
};