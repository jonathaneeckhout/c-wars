#include "entities/Entity.h"

Entity::Entity(std::string id, Map *map, Vector position) : id(id), map(map), position(position) {}

Entity::~Entity() {}