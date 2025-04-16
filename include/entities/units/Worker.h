#pragma once

#include <string>

#include "entities/units/Unit.h"

class Worker : public Unit
{
public:
    Worker(std::string id, std::string player, Map *map, Vector position);
    ~Worker();
};