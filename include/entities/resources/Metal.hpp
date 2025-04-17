#pragma once

#include "entities/resources/Resource.hpp"

class Metal : public Resource
{
public:
    Metal(std::string id, Map *map, Vector position);
    ~Metal();
};