#include "entities/Worker.h"

Worker::Worker(std::string id, std::string player, Vector position) : Unit(id, player, position)
{
    name = "Worker";
}

Worker::~Worker() {}
