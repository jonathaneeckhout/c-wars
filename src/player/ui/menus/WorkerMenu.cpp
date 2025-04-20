#include "player/ui/menus/WorkerMenu.hpp"

WorkerMenu::WorkerMenu() {}

WorkerMenu::~WorkerMenu() {}

void WorkerMenu::input() {}

void WorkerMenu::update(float) {}

void WorkerMenu::output(Renderer *renderer)
{
    if (!visible)
    {
        return;
    }

    SDL_FRect rect = {position.x, position.y, size.x, size.y};
    SDL_SetRenderDrawColor(renderer->renderer, 32, 32, 32, 255);
    SDL_RenderFillRectF(renderer->renderer, &rect);
}