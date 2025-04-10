#include <iostream>

#include "Player.h"
#include "entities/Unit.h"
#include "collision/CollisionShapeSquare.h"

Player::Player() {}

Player::~Player() {}

void Player::scanEntities(SDL_FRect rect, std::map<std::string, Entity *> &entities)
{
    CollisionShapeSquare collisionShape = {{rect.x, rect.y}, {rect.w, rect.h}};
    for (auto entity : entities)
    {
        if (dynamic_cast<Unit *>(entity.second))
        {
            Unit *unit = dynamic_cast<Unit *>(entity.second);
            if (collisionShape.collidesWith(unit->collisionShape))
            {
                std::cout << "Collided with unit:" << unit->id << std::endl;

                // TODO: Select unit
            }
        }
    }
}