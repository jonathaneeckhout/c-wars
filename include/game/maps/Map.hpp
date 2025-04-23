#pragma once

#include "engine/entities/Entity.hpp"
#include "game/player/Player.hpp"
#include "game/entities/units/Unit.hpp"

class Map : public Entity
{
public:
    Map(std::string name);
    ~Map();

    Player *getPlayer(const std::string &name);
    bool addPlayer(const std::string &name, const bool &isLocal);
    bool removePlayer(const std::string &name);

    Unit *getUnit(const std::string &id);
    bool addUnit(const std::string &type, const std::string &player, Vector pos);
    bool removeUnit(const std::string &id);

private:
    Object *players = nullptr;
    Object *units = nullptr;
    Object *resources = nullptr;
};