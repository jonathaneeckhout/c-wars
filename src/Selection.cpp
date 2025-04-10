#include "Selection.h"

Selection::Selection() {}

Selection::~Selection() {}

void Selection::start(Vector position)
{
    selected = true;
    startPos = position;
    endPos = position;
}

void Selection::move(Vector position)
{
    if (!selected)
    {
        return;
    }

    endPos = position;
}

void Selection::end(Vector position)
{
    selected = false;
    endPos = position;

    if (onSelection != NULL)
    {
        onSelection(getSelectionRect());
    }
}

void Selection::output(SDL_Renderer *renderer, Camera *)
{
    if (selected)
    {
        SDL_FRect square = getSelectionRect();
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
        SDL_RenderFillRectF(renderer, &square);
    }
}

SDL_FRect Selection::getSelectionRect() const
{
    float minX = std::min(int(startPos.x), int(endPos.x));
    float minY = std::min(int(startPos.y), int(endPos.y));
    float width = std::abs(int(endPos.x - startPos.x));
    float height = std::abs(int(endPos.y - startPos.y));
    return {minX, minY, width, height};
}