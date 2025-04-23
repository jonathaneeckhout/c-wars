#include "game/entities/units/Worker.hpp"
#include "engine/core/Renderer.hpp"
#include "engine/ui/text/Label.hpp"

Worker::Worker(const std::string &player, Vector position) : Unit(player, "Worker", position)
{

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