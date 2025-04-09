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
        SDL_Rect square = getSelectionRect();
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
        SDL_RenderFillRect(renderer, &square);
    }
}

SDL_Rect Selection::getSelectionRect() const
{
    int minX = std::min(int(startPos.x), int(endPos.x));
    int minY = std::min(int(startPos.y), int(endPos.y));
    int width = std::abs(int(endPos.x - startPos.x));
    int height = std::abs(int(endPos.y - startPos.y));
    return {minX, minY, width, height};
}