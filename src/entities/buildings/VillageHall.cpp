#include "entities/buildings/VillageHall.h"

VillageHall::VillageHall(std::string id, std::string player, Map *map, Vector position) : Building(id, player, map, position)
{
    name = "VillageHall";

    color = {218, 165, 32, 255};
}

VillageHall::~VillageHall() {};