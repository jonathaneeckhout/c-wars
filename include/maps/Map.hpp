#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "entities/Entity.hpp"
#include "utils/Vector.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

class Map
{
public:
    std::string name = "";

    std::map<std::string, std::unique_ptr<Entity>> entities;

    Map(std::string name);
    ~Map();

    void update(float dt);
    void output(Renderer *renderer, Camera *camera);

    Entity *getEntity(const std::string &id);
    std::string addEntity(const std::string &name, const std::string &player, Vector position);
    void removeEntity(const std::string &id);

    std::vector<Entity *> getEntities() const;
    std::vector<Entity *> getEntitiesInRect(SDL_FRect rect);
};
