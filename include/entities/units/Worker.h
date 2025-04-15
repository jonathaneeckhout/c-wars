#pragma once

#include <string>

#include "entities/units/Unit.h"

class Worker : public Unit
{
public:
    Worker(std::string id, std::string player, Vector position);
    ~Worker();
};