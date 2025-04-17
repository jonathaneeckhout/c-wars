#pragma once

#include "entities/buildings/Building.h"

class VillageHall : public Building
{
public:
    VillageHall(std::string id, std::string player, Map *map, Vector position);
    ~VillageHall();
};