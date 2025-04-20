#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "player/Player.hpp"
#include "entities/Entity.hpp"
#include "utils/Vector.hpp"
#include "core/Renderer.hpp"

class Map
{
public:
    std::string name = "";

    std::map<std::string, std::unique_ptr<Player>> players;
    std::map<std::string, std::unique_ptr<Entity>> entities;

    Map(std::string name);
    ~Map();

    void input();
    void update(float dt);
    void output(Renderer *renderer);

    Player *getPlayer(const std::string &name);
    bool addPlayer(const std::string &name, bool isLocal);
    void removePlayer(const std::string &name);

    Entity *getEntity(const std::string &id);
    std::string addEntity(const std::string &name, const std::string &player, Vector position);
    void removeEntity(const std::string &id);

    std::vector<Entity *> getEntities() const;
    std::vector<Entity *> getEntitiesInRect(SDL_FRect rect);

private:
};
