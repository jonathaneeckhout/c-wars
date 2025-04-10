#pragma once
#include <string>
#include <map>
#include <SDL2/SDL.h>

#include "entities/Entity.h"

class Player
{
public:
    std::string name;

    Player();
    ~Player();

    void scanEntities(SDL_FRect rect, std::map<std::string, Entity *> &entities);

private:
    std::map<std::string, Entity *> selectedEntities;
};