#include <iostream>

#include "maps/Map.hpp"
#include "utils/uuid.hpp"
#include "collision/CollisionShapeSquare.hpp"
#include "entities/units/Worker.hpp"
#include "entities/resources/Metal.hpp"
#include "entities/buildings/VillageHall.hpp"

Map::Map(std::string name, Renderer *renderer) : name(name), renderer(renderer) {}

Map::~Map() {}

void Map::input()
{
    for (auto &pair : players)
    {
        pair.second->input();
    }
}

void Map::update(float dt)
{
    for (auto &pair : entities)
    {
        pair.second->update(dt);
    }

    for (auto &pair : players)
    {
        pair.second->update(dt);
    }
}

void Map::output(Renderer *renderer)
{
    for (auto &pair : entities)
    {
        pair.second->output(renderer);
    }

    for (auto &pair : players)
    {
        pair.second->output(renderer);
    }
}

Player *Map::getPlayer(const std::string &name)
{
    auto it = players.find(name);
    if (it != players.end())
    {
        return it->second.get();
    }
    return nullptr;
}

bool Map::addPlayer(const std::string &name, bool isLocal)
{
    if (getPlayer(name) != nullptr)
    {
        return false;
    }

    players[name] = std::make_unique<Player>(name, this, isLocal, renderer);
    return true;
}

void Map::removePlayer(const std::string &name)
{
    players.erase(name);
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
        entities[id] = std::make_unique<Worker>(id, player, this, position);
        return id;
    }
    else if (name == "Metal")
    {
        entities[id] = std::make_unique<Metal>(id, this, position);
        return id;
    }
    else if (name == "VillageHall")
    {
        entities[id] = std::make_unique<VillageHall>(id, player, this, position);
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

std::vector<Entity *> Map::getEntitiesInRect(SDL_FRect rect)
{
    std::vector<Entity *> result;

    CollisionShapeSquare collisionShape = {{rect.x, rect.y}, {rect.w, rect.h}};

    for (const auto &pair : entities)
    {
        if (pair.second->collisionShape == NULL)
        {
            continue;
        }

        if (pair.second->collisionShape->collidesWith(collisionShape))
        {
            result.push_back(pair.second.get());
        }
    }
    return result;
}
