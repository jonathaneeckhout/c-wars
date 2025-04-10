#include "entities/Entity.h"

Entity::Entity(std::string id, Vector position) : id(id), position(position)
{
}

Entity::~Entity() {}