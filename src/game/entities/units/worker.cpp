#include "game/entities/units/Worker.hpp"
#include "engine/entities/collision/CollisionShapeSquare.hpp"
#include "engine/ui/text/Label.hpp"

Worker::Worker(const std::string &player, Vector position) : Unit(player, "Worker", position)
{
    selectionArea = new CollisionShapeSquare(position, Vector{32, 32});

    Label *label = new Label(position, "Worker");

    addChild(label);
}

Worker::~Worker() {}

void Worker::input()
{
}

void Worker::update(float)
{
}

void Worker::output()
{
}