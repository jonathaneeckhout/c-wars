#include <iostream>

#include "Player.h"
#include "entities/Unit.h"
#include "collision/CollisionShapeSquare.h"

Player::Player() {}

Player::~Player() {}

void Player::scanEntities(SDL_FRect rect, std::vector<Entity *> entities)
{
    // Clear selected entities
    deselectAll();

    selectedEntities.clear();

    CollisionShapeSquare collisionShape = {{rect.x, rect.y}, {rect.w, rect.h}};
    for (auto entity : entities)
    {
        if (dynamic_cast<Unit *>(entity))
        {
            Unit *unit = dynamic_cast<Unit *>(entity);
            if (collisionShape.collidesWith(unit->collisionShape))
            {
                selectedEntities.addMember(unit->id);
            }
        }
    }

    selectAll();
}

void Player::selectAll()
{
    for (const std::string &id : selectedEntities.getMembers())
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
    for (const std::string &id : selectedEntities.getMembers())
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
