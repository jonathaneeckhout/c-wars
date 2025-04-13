#include "entities/Unit.h"

Unit::Unit(std::string id, std::string player, Vector position) : Entity(id, position)
{
    this->player = player;
    collisionShape.position = position;
}

Unit::~Unit() {}

void Unit::update(float dt)
{
    position += velocity * dt;
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