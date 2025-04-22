#include "game/maps/Map.hpp"

Map::Map(std::string name)
{
    this->name = name;

    players = new Object();
    players->name = "Players";
    this->addChild(players);

    units = new Object();
    units->name = "Units";
    this->addChild(units);
}

Map::~Map() {}

Player *Map::getPlayer(const std::string &name)
{
    return dynamic_cast<Player *>(players->getChildByName(name));
}

bool Map::addPlayer(const std::string &name, const bool &isLocal)
{
    if (players->getChildByName(name) != nullptr)
    {
        return false;
    }

    return players->addChild(new Player(name, isLocal));
}

bool Map::removePlayer(const std::string &name)
{
    return players->deleteChild(name);
}

Unit *Map::getUnit(const std::string &name)
{
    return dynamic_cast<Unit *>(units->getChildByName(name));
}

bool Map::addUnit(const std::string &name, const std::string &player)
{
}