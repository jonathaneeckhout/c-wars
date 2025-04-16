#include <iostream>

#include "entities/units/Worker.h"

Worker::Worker(std::string id, std::string player, Map *map, Vector position) : Unit(id, player, map, position)
{
    name = "Worker";

    color = {0, 0, 255, 255};
}

Worker::~Worker() {}
