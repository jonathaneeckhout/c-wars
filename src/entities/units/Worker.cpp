#include <iostream>

#include "entities/units/Worker.hpp"

Worker::Worker(std::string id, std::string player, Map *map, Vector position) : Unit(id, player, map, position)
{
    name = "Worker";

    color = {0, 0, 255, 255};

    gatherTimer = new Timer(1.0);

    gatherTimer->setCallback([this](void *)
                             { this->gatherCallback(); });
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
        state = UnitState::Idle;
    }
    else
    {
        float distance = position.distanceTo(resource->position);
        if (distance > interactionRange)
        {
            state = UnitState::Moving;

            velocity = position.directionTo(resource->position);
        }
        else
        {
            state = UnitState::Gathering;

            targetPosition = position;
            velocity = {0, 0};

            if (!gatherTimer->isRunning())
            {
                gatherTimer->start();
            }
        }
    }
}

void Worker::gatherCallback()
{
    Resource *resource = getTargetResource();
    if (resource == NULL)
    {
        return;
    }

    float distance = position.distanceTo(resource->position);
    if (distance > interactionRange)
    {
        return;
    }

    std::pair<std::string, float> material = resource->gather(gatherSpeed);

    bag.add(material);
}