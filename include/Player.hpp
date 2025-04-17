#pragma once
#include <string>
#include <map>
#include <SDL2/SDL.h>

#include "maps/Map.hpp"
#include "entities/Entity.hpp"
#include "Group.hpp"

class Player
{
public:
    std::string name = "";

    Player(std::string name);
    ~Player();

    void setMap(Map *map);

    void selectEntities(std::vector<Entity *> entities);
    void interact(Vector position, std::vector<Entity *> entities);

private:
    Map *map = NULL;

    Group *selectedEntities = NULL;

    void selectAll();
    void deselectAll();
};