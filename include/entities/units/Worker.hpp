#pragma once

#include <string>

#include "entities/units/Unit.hpp"
#include "Bag.hpp"
#include "utils/Timer.hpp"
#include "entities/buildings/Building.hpp"

class Worker : public Unit
{
public:
    float gatherSpeed = 10.0f;

    Worker(std::string id, std::string player, Map *map, Vector position);
    ~Worker();

    void update(float dt) override;

    void handleResourceUpdate(Resource *resource, float dt) override;

    void gatherCallback();

protected:
    Bag bag;

    Timer *gatherTimer = NULL;

    std::string storageID = "";

    Building *findClosestStorage();
};