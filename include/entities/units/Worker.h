#pragma once

#include <string>

#include "entities/units/Unit.h"
#include "Bag.h"
#include "utils/Timer.h"

class Worker : public Unit
{
public:
    float gatherSpeed = 10.0f;

    Worker(std::string id, std::string player, Map *map, Vector position);
    ~Worker();

    void update(float dt) override;

    void handleResourceUpdate(Resource *resource, float dt) override;

    void gatherCallback();

private:
    Bag bag;

    Timer *gatherTimer = NULL;
};