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

    UnitState state = UnitState::Idle;

    Unit(const std::string &player, const std::string &name, Vector position);
    ~Unit();
};