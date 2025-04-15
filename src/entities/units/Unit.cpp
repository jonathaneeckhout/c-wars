#include <iostream>

#include "entities/units/Unit.h"
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

    // Center the collisionshape
    collisionShape->position = position - renderOffset;
}

void Unit::output(Renderer *renderer, Camera *camera)
{
    SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_NONE);

    Vector renderPostion = position - camera->position;

    Vector unitRenderPosition = renderPostion - renderOffset;

    // Draw selected area
    if (selected)
    {
        SDL_FRect selectedSquare = {unitRenderPosition.x - selectedRenderOffset.x, unitRenderPosition.y - selectedRenderOffset.y, selectedSize.x, selectedSize.y};
        SDL_SetRenderDrawColor(renderer->renderer, selectColor.r, selectColor.g, selectColor.b, selectColor.a);
        SDL_RenderFillRectF(renderer->renderer, &selectedSquare);
    }

    drawName(renderer, renderPostion, Vector{0, -48});
    drawPlayer(renderer, renderPostion, Vector{0, -64});

    // Draw Unit
    SDL_FRect square = {unitRenderPosition.x, unitRenderPosition.y, size.x, size.y};
    SDL_SetRenderDrawColor(renderer->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRectF(renderer->renderer, &square);

    SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_ADD);
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

void Unit::drawName(Renderer *renderer, Vector position, Vector offset)
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

void Unit::drawPlayer(Renderer *renderer, Vector position, Vector offset)
{
    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Surface *textSurface = TTF_RenderText_Solid(renderer->fonts["unit"], player.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer->renderer, textSurface);

    SDL_FRect textRect = {position.x - float(textSurface->w) / 2 + offset.x, position.y + offset.y, float(textSurface->w), float(textSurface->h)};
    SDL_RenderCopyF(renderer->renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}