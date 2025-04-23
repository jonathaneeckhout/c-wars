#include "game/entities/units/Unit.hpp"

Unit::Unit(const std::string &player, const std::string &name, Vector position) : GameObject(position), player(player)
{
    this->name = name;
};

Unit::~Unit() {};