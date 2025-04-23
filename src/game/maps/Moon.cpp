#include "game/maps/Moon.hpp"

Moon::Moon() : Map("Moon")
{
    addPlayer("Player", true);

    addPlayer("Computer", false);

    addUnit("Worker", "Player", Vector(400, 300));

    // addUnit("Worker", "Computer", Vector(400, -300));
}

Moon::~Moon() {}