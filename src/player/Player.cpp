#include <iostream>
#include <signal.h>

#include "player/Player.hpp"
#include "maps/Map.hpp"
#include "entities/units/Unit.hpp"
#include "Game.hpp"

Player::Player(std::string name, Map *map, bool isLocal, Renderer *renderer) : name(name), map(map), isLocal(isLocal)
{
    selectedEntities = new Group(name, map);

    if (isLocal)
    {
        controls = new Controls();
        camera = new Camera();

        renderer->currentCamera = camera;

        registerInputs();
    }
}

Player::~Player()
{
    delete selectedEntities;

    if (isLocal)
    {
        delete controls;
        delete camera;
    }
}

void Player::input()
{
    if (!isLocal)
    {
        return;
    }

    controls->input();
}

void Player::update(float dt)
{
    if (!isLocal)
    {
        return;
    }

    camera->update(dt);
}

void Player::output(Renderer *renderer)
{
    if (!isLocal)
    {
        return;
    }

    controls->output(renderer, camera);

    drawResources(renderer, {16, 16});
}

void Player::registerInputs()
{
    controls->onStop = []()
    {
        Game *game = Game::getInstance();

        game->stop();
    };

    controls->onMoveCamera = [this](Vector direction)
    {
        camera->move(direction);
    };

    controls->onSelection = [this](SDL_FRect rect)
    {
        SDL_FRect globalRect = rect;
        globalRect.x += camera->position.x;
        globalRect.y += camera->position.y;

        std::vector<Entity *> entities = map->getEntitiesInRect(globalRect);

        this->selectEntities(entities);
    };

    controls->onInteract = [this](Vector position)
    {
        Vector globalPosition = position;
        globalPosition.x += camera->position.x;
        globalPosition.y += camera->position.y;

        SDL_FRect globalRect = {globalPosition.x, globalPosition.y, 0, 0};

        std::vector<Entity *> entities = map->getEntitiesInRect(globalRect);

        this->interact(globalPosition, entities);
    };
}

void Player::selectEntities(std::vector<Entity *> entities)
{
    // Clear selected entities
    deselectAll();

    selectedEntities->clear();

    for (auto entity : entities)
    {
        selectedEntities->addMember(entity->id);
    }

    selectAll();
}

void Player::interact(Vector position, std::vector<Entity *> entities)
{
    if (entities.size() == 0)
    {
        selectedEntities->move(position);
    }
    else
    {
        // For now only interact with the first one
        selectedEntities->interact(entities[0]);
    }
}

void Player::selectAll()
{
    for (const std::string &id : selectedEntities->getMembers())
    {
        Entity *entity = map->getEntity(id);
        if (!entity)
            continue;

        if (Unit *unit = dynamic_cast<Unit *>(entity))
        {
            unit->select();
        }
    }
}

void Player::deselectAll()
{
    for (const std::string &id : selectedEntities->getMembers())
    {
        Entity *entity = map->getEntity(id);
        if (!entity)
            continue;

        if (Unit *unit = dynamic_cast<Unit *>(entity))
        {
            unit->deselect();
        }
    }
}

void Player::drawResources(Renderer *renderer, Vector offset)
{
    SDL_Color textColor = {255, 255, 255, 255};

    std::string resourcesString = "Metal: " + std::to_string(static_cast<int>(resources.metal));

    SDL_Surface *textSurface = TTF_RenderText_Solid(renderer->fonts["unit"], resourcesString.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer->renderer, textSurface);

    SDL_FRect textRect = {offset.x, offset.y, float(textSurface->w), float(textSurface->h)};
    SDL_RenderCopyF(renderer->renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}