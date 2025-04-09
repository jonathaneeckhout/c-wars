#include "entities/Worker.h"

Worker::Worker(Vector position) : Entity(position) {}

Worker::~Worker() {}

void Worker::update(float dt)
{
    position += velocity * dt;
}

void Worker::output(SDL_Renderer *renderer, Camera *camera)
{
    Vector renderPostion = position - camera->position;
    SDL_Rect square = {int(renderPostion.x), int(renderPostion.y), 32, 32}; // x, y, width, height
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);                         // Red square
    SDL_RenderFillRect(renderer, &square);
}