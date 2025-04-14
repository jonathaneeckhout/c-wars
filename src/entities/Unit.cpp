#include <iostream>

#include "entities/Unit.h"
#include "collision/CollisionShapeSquare.h"

Unit::Unit(std::string id, std::string player, Vector position) : Entity(id, position)
{
    this->player = player;
    targetPosition = position;

    collisionShape = new CollisionShapeSquare(position, {32, 32});
}

Unit::~Unit()
{
    delete collisionShape;
}

void Unit::update(float dt)
{
    if (position.distanceTo(targetPosition) < arrivalRadius)
    {
        velocity = {0, 0};
    }
    else
    {
        velocity = targetPosition - position;

        velocity = velocity.normalize();
    }

    position += velocity * speed * dt;
    collisionShape->position = position;
}

void Unit::output(SDL_Renderer *renderer, Camera *camera)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    Vector renderPostion = position - camera->position;
    if (selected)
    {
        SDL_FRect selectedSquare = {renderPostion.x - 1, renderPostion.y - 1, 34, 34};
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRectF(renderer, &selectedSquare);
    }

    SDL_FRect square = {renderPostion.x, renderPostion.y, 32, 32};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRectF(renderer, &square);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
}

void Unit::select()
{
    selected = true;
}

void Unit::deselect()
{
    selected = false;
}

void Unit::move(Vector position)
{
    targetPosition = position;
}