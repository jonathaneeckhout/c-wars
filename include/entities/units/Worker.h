#pragma once

#include <string>

#include "entities/units/Unit.h"
#include "Bag.h"
#include "utils/Timer.h"

class Worker : public Unit
{
public:
    Worker(std::string id, std::string player, Map *map, Vector position);
    ~Worker();

    void update(float dt) override;

    void handleResourceUpdate(Resource *resource, float dt) override;

private:
    Bag bag;

    Timer *gatherTimer = NULL;
};