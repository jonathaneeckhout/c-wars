#pragma once

#include "engine/Object.hpp"
#include "engine/Camera.hpp"

class Player : public Object
{
public:
    bool isLocal = false;

    Player(const std::string &name);
    Player(const std::string &name, const bool &isLocal);
    virtual ~Player();

private:
    Camera *camera = nullptr;
};