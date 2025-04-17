#pragma once

#include "entities/buildings/Building.hpp"

class VillageHall : public Building
{
public:
    VillageHall(std::string id, std::string player, Map *map, Vector position);
    ~VillageHall();
};