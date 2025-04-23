#pragma once

#include "game/entities/units/Unit.hpp"

class Worker : public Unit
{
public:
    Worker(const std::string &player, Vector position);
    ~Worker();

private:
    void input() override;
    void update(float dt) override;
    void output() override;
};