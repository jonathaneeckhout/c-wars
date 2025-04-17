#include <iostream>

#include "entities/units/Worker.hpp"
#include "maps/Map.hpp"

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
        Building *storage = NULL;

        if (storageID.empty())
        {
            storage = findClosestStorage();
        }
        else
        {
            Entity *entity = map->getEntity(storageID);
            if (entity == NULL)
            {
                state = UnitState::Idle;

                storageID = "";
                return;
            }

            storage = dynamic_cast<Building *>(entity);
            if (storage == NULL)
            {
                state = UnitState::Idle;

                storageID = "";

                return;
            }
        }

        storageID = storage->id;

        float distance = position.distanceTo(storage->position);
        if (distance > interactionRange)
        {
            state = UnitState::Moving;

            velocity = position.directionTo(storage->position);
        }
        else
        {
            state = UnitState::Store;

            velocity = {0, 0};

            storageID = "";

            storage->store(bag.empty());
        }
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

Building *Worker::findClosestStorage()
{
    Building *storage = NULL;
    float closestDistance = 0.0f;

    std::vector<Entity *> entities = map->getEntities();

    for (auto entity : entities)
    {
        Building *building = dynamic_cast<Building *>(entity);
        if (building == NULL)
        {
            continue;
        }

        if (!building->storage)
        {
            continue;
        }

        if (player != building->player)
        {
            continue;
        }

        float distance = position.distanceTo(building->position);

        if (storage == NULL)
        {
            storage = building;
            closestDistance = distance;
        }
        else
        {
            if (distance < closestDistance)
            {
                storage = building;
                closestDistance = distance;
            }
        }
    }

    return storage;
}