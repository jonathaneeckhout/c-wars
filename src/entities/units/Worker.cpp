#include <iostream>

#include "entities/units/Worker.h"

Worker::Worker(std::string id, std::string player, Vector position) : Unit(id, player, position)
{
    name = "Worker";

    color = {0, 0, 255, 255};
}

Worker::~Worker() {}
