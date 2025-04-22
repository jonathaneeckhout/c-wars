#include "game/maps/Moon.hpp"

Moon::Moon() : Map("Moon")
{
    addPlayer("Player", true);

    addPlayer("Computer", false);
}

Moon::~Moon() {}