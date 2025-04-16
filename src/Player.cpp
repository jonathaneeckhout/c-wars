#include <iostream>

#include "Player.h"
#include "entities/units/Unit.h"

Player::Player(std::string name) : name(name)
{
    selectedEntities = new Group(name);
}

Player::~Player()
{
    delete selectedEntities;
}

void Player::setMap(Map *map)
{
    this->map = map;

    selectedEntities->map = map;
}

void Player::selectEntities(std::vector<Entity *> entities)
{
    // Clear selected entities
    deselectAll();

    selectedEntities->clear();

    for (auto entity : entities)
    {
        selectedEntities->addMember(entity->id);
    }

    selectAll();
}

void Player::interact(Vector position, std::vector<Entity *> entities)
{
    if (entities.size() == 0)
    {
        selectedEntities->move(position);
    }
    else
    {
        // For now only interact with the first one
        selectedEntities->interact(entities[0]);
    }
}

void Player::selectAll()
{
    for (const std::string &id : selectedEntities->getMembers())
    {
        Entity *entity = map->getEntity(id);
        if (!entity)
            continue;

        if (Unit *unit = dynamic_cast<Unit *>(entity))
        {
            unit->select();
        }
    }
}

void Player::deselectAll()
{
    for (const std::string &id : selectedEntities->getMembers())
    {
        Entity *entity = map->getEntity(id);
        if (!entity)
            continue;

        if (Unit *unit = dynamic_cast<Unit *>(entity))
        {
            unit->deselect();
        }
    }
}
