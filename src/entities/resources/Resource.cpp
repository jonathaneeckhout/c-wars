#include "entities/resources/Resource.hpp"
#include "collision/CollisionShapeSquare.hpp"

Resource::Resource(std::string id, Map *map, Vector position) : Entity(id, map, position)
{
    collisionShape = new CollisionShapeSquare(position - renderOffset, {32, 32});
}

Resource::~Resource()
{
    delete collisionShape;
}

void Resource::update(float) {}

void Resource::output(Renderer *renderer)
{
    SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_NONE);

    Vector renderPostion = position - renderer->currentCamera->position;

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

std::pair<std::string, float> Resource::gather(float amount)
{
    return {type, amount * speed};
}