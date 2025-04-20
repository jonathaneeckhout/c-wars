#include <iostream>

#include "maps/Moon.hpp"

Moon::Moon() : Map("Moon")
{
    // Add Players
    addPlayer("TestPlayer", true);
    addPlayer("Computer", false);

    // Add Resources
    addEntity("Metal", "", Vector(400 - 128, 300));
    // Add Units
    addEntity("Worker", "TestPlayer", Vector(400, 300));
    addEntity("Worker", "Computer", Vector(400, -300));

    // Add Buildings
    addEntity("VillageHall", "TestPlayer", Vector(400 + 128, 300));
}

Moon::~Moon() {}