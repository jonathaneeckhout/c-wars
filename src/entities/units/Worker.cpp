#include <iostream>

#include "entities/units/Worker.h"

Worker::Worker(std::string id, std::string player, Map *map, Vector position) : Unit(id, player, map, position)
{
    name = "Worker";

    color = {0, 0, 255, 255};

    gatherTimer = new Timer(1.0);
}

Worker::~Worker()
{
    delete gatherTimer;
}

void Worker::update(float dt)
{
    Unit::update(dt);

    gatherTimer->update(dt);
}

void Worker::handleResourceUpdate(Resource *resource, float)
{
    if (bag.isFull())
    {
        // TODO: move towards storage
    }
    else
    {
        float distance = position.distanceTo(resource->position);
        if (distance > interactionRange)
        {
            velocity = position.directionTo(resource->position);
        }
        else
        {
            targetPosition = position;
            velocity = {0, 0};

            // TODO: gather
            if (!gatherTimer->isRunning())
            {
                gatherTimer->start();
            }
        }
    }
}
