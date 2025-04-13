#include <iostream>

#include "maps/Map.h"
#include "utils/uuid.h"
#include "entities/Worker.h"

Map::Map() = default;
Map::~Map() = default; // optional, since unique_ptr handles cleanup

void Map::update(float dt)
{
    for (auto &pair : entities)
    {
        pair.second->update(dt);
    }
}

void Map::output(SDL_Renderer *renderer, Camera *camera)
{
    for (auto &pair : entities)
    {
        pair.second->output(renderer, camera);
    }
}

Entity *Map::getEntity(const std::string &id)
{
    auto it = entities.find(id);
    if (it != entities.end())
    {
        return it->second.get();
    }
    return nullptr;
}

std::string Map::addEntity(const std::string &name, const std::string &player, Vector position)
{
    std::string id = generate_uuid();

    if (name == "Worker")
    {
        entities[id] = std::make_unique<Worker>(id, player, position);
        return id;
    }

    return "";
}

void Map::removeEntity(const std::string &id)
{
    entities.erase(id);
}

std::vector<Entity *> Map::getEntities() const
{
    std::vector<Entity *> result;
    for (const auto &pair : entities)
    {
        result.push_back(pair.second.get());
    }
    return result;
}
