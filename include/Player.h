#pragma once
#include <string>
#include <map>
#include <SDL2/SDL.h>

#include "maps/Map.h"
#include "entities/Entity.h"
#include "Group.h"

class Player
{
public:
    std::string name;

    Map *map = NULL;

    Player();
    ~Player();

    void scanEntities(SDL_FRect rect, std::vector<Entity *>entities);

private:
    Group selectedEntities;

    void selectAll();
    void deselectAll();
};