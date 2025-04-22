#pragma once

#include "game/entities/GameObject.hpp"

enum class UnitState
{
    Idle,
    Moving,
    Gathering,
    Store,
    Attacking,
    Building
};

class Unit : public GameObject
{
public:
    std::string player = "";

    float speed = 100.0f;

    Unit();
    ~Unit();
};