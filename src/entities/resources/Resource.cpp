#include "entities/resources/Resource.h"
#include "collision/CollisionShapeSquare.h"

Resource::Resource(std::string id, Map *map, Vector position) : Entity(id, map, position)
{
    collisionShape = new CollisionShapeSquare(position - renderOffset, {32, 32});
}

Resource::~Resource()
{
    delete collisionShape;
}

void Resource::update(float) {}

void Resource::output(Renderer *renderer, Camera *camera)
{
    SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_NONE);

    Vector renderPostion = position - camera->position;

    Vector resourceRenderPosition = renderPostion - renderOffset;

    // Draw selected area
    if (selected)
    {
        SDL_FRect selectedSquare = {resourceRenderPosition.x - selectedRenderOffset.x, resourceRenderPosition.y - selectedRenderOffset.y, selectedSize.x, selectedSize.y};
        SDL_SetRenderDrawColor(renderer->renderer, selectColor.r, selectColor.g, selectColor.b, selectColor.a);
        SDL_RenderFillRectF(renderer->renderer, &selectedSquare);
    }

    // Draw Resource
    SDL_FRect square = {resourceRenderPosition.x, resourceRenderPosition.y, size.x, size.y};
    SDL_SetRenderDrawColor(renderer->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRectF(renderer->renderer, &square);

    drawName(renderer, renderPostion, Vector{0, -48});

    SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_ADD);
}

void Resource::drawName(Renderer *renderer, Vector position, Vector offset)
{
    if (name.empty())
    {
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Surface *textSurface = TTF_RenderText_Solid(renderer->fonts["unit"], name.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer->renderer, textSurface);

    SDL_FRect textRect = {position.x - float(textSurface->w) / 2 + offset.x, position.y + offset.y, float(textSurface->w), float(textSurface->h)};
    SDL_RenderCopyF(renderer->renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

std::pair<std::string, float> Resource::gather(float amount)
{
    return {type, amount * speed};
}