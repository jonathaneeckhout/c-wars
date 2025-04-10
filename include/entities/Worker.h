#pragma once

#include <string>

#include "entities/Unit.h"

class Worker : public Unit
{
public:
    bool selected = false;

    Worker(std::string id, std::string player, Vector position);
    ~Worker();
};