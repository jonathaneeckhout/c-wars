#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "entities/Entity.h"
#include "utils/Vector.h"
#include "Camera.h"

class Map
{
public:
    std::string name;

    std::map<std::string, std::unique_ptr<Entity>> entities;

    Map();
    ~Map(); // optional to define now

    void update(float dt);
    void output(SDL_Renderer *renderer, Camera *camera);

    std::vector<Entity *> getEntities() const;

    Entity *getEntity(const std::string &id);
    std::string addEntity(const std::string &name, const std::string &player, Vector position);
    void removeEntity(const std::string &id);
};
