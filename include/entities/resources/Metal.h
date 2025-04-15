#pragma once

#include "entities/resources/Resource.h"

class Metal : public Resource
{
public:
    Metal(std::string id, Vector position);
    ~Metal();
};