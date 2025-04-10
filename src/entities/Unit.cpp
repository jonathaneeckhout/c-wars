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
    Vector renderPostion = position - camera->position;
    SDL_FRect square = {renderPostion.x, renderPostion.y, 32, 32};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRectF(renderer, &square);
}