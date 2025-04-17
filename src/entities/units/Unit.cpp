#include <iostream>

#include "entities/units/Unit.hpp"
#include "collision/CollisionShapeSquare.hpp"
#include "maps/Map.hpp"

Unit::Unit(std::string id, std::string player, Map *map, Vector position) : Entity(id, map, position), player(player)
{
    targetPosition = position;

    collisionShape = new CollisionShapeSquare(position - renderOffset, {32, 32});
}

Unit::~Unit()
{
    delete collisionShape;
}

void Unit::update(float dt)
{
    if (!targetID.empty())
    {
        handleInteractUpdate(dt);
    }
    else
    {
        handleMoveUpdate(dt);
    }

    position += velocity * speed * dt;

    // Center the collisionshape
    collisionShape->position = position - renderOffset;
}

void Unit::handleMoveUpdate(float)
{
    if (position.distanceTo(targetPosition) < arrivalRadius)
    {
        state = UnitState::Idle;

        velocity = {0, 0};
    }
    else
    {
        state = UnitState::Moving;

        velocity = position.directionTo(targetPosition);
    }
}

void Unit::handleInteractUpdate(float dt)
{
    Entity *target = getTargetEntity();
    if (target == NULL)
    {
        return;
    }

    Resource *resource = dynamic_cast<Resource *>(target);
    if (resource != NULL)
    {
        handleResourceUpdate(resource, dt);
    }
    else
    {
        float distance = position.distanceTo(target->position);
        if (distance > interactionRange)
        {
            state = UnitState::Moving;

            velocity = position.directionTo(target->position);
        }
        else
        {
            state = UnitState::Idle;

            velocity = {0, 0};
        }
    }
}

void Unit::handleResourceUpdate(Resource *resource, float)
{
    // Default unit behavior for resource is to just move towards it
    float distance = position.distanceTo(resource->position);
    if (distance > interactionRange)
    {
        state = UnitState::Moving;

        velocity = position.directionTo(resource->position);
    }
    else
    {
        state = UnitState::Idle;

        targetID = "";
        targetPosition = position;
        velocity = {0, 0};
    }
}

void Unit::output(Renderer *renderer)
{
    SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_NONE);

    Vector renderPostion = position - renderer->currentCamera->position;

    Vector unitRenderPosition = renderPostion - renderOffset;

    // Draw selected area
    if (selected)
    {
        SDL_FRect selectedSquare = {unitRenderPosition.x - selectedRenderOffset.x, unitRenderPosition.y - selectedRenderOffset.y, selectedSize.x, selectedSize.y};
        SDL_SetRenderDrawColor(renderer->renderer, selectColor.r, selectColor.g, selectColor.b, selectColor.a);
        SDL_RenderFillRectF(renderer->renderer, &selectedSquare);
    }

    // Draw Unit
    SDL_FRect square = {unitRenderPosition.x, unitRenderPosition.y, size.x, size.y};
    SDL_SetRenderDrawColor(renderer->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRectF(renderer->renderer, &square);

    drawName(renderer, renderPostion, Vector{0, -48});
    drawPlayer(renderer, renderPostion, Vector{0, -64});
    drawState(renderer, renderPostion, Vector{0, -16});

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
    targetID = "";
}

void Unit::interact(std::string target)
{
    targetID = target;
}

Entity *Unit::getTargetEntity()
{
    Entity *target = map->getEntity(targetID);
    if (target == NULL)
    {
        targetID = "";
        targetPosition = position;
    }

    return target;
}

Resource *Unit::getTargetResource()
{
    Entity *target = getTargetEntity();
    if (target == NULL)
    {
        return NULL;
    }

    return dynamic_cast<Resource *>(target);
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

void Unit::drawState(Renderer *renderer, Vector position, Vector offset)
{
    SDL_Color textColor = {255, 255, 255, 255};

    std::string stateText = "I";

    switch (state)
    {
    case UnitState::Idle:
        stateText = "I";
        break;
    case UnitState::Moving:
        stateText = "M";
        break;
    case UnitState::Gathering:
        stateText = "G";
        break;
    case UnitState::Store:
        stateText = "S";
        break;
    case UnitState::Attacking:
        stateText = "A";
        break;
    case UnitState::Building:
        stateText = "B";
        break;
    default:
        break;
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(renderer->fonts["unit"], stateText.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer->renderer, textSurface);

    SDL_FRect textRect = {position.x - float(textSurface->w) / 2 + offset.x, position.y + offset.y, float(textSurface->w), float(textSurface->h)};
    SDL_RenderCopyF(renderer->renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}