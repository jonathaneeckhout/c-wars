#include <iostream>

#include "player/Player.hpp"
#include "maps/Map.hpp"
#include "player/ui/UI.hpp"
#include "entities/units/Unit.hpp"
#include "entities/units/Worker.hpp"

Player::Player(std::string name, Map *map, bool isLocal) : name(name), map(map), isLocal(isLocal)
{
    selectedEntities = new Group(name, map);

    if (!isLocal)
    {
        return;
    }

    camera = new Camera();

    ui = new UI(this);

    Renderer::getInstance()->currentCamera = camera;

    registerInputs();
}

Player::~Player()
{
    delete selectedEntities;

    if (!isLocal)
    {
        return;
    }

    delete ui;

    delete camera;
}

void Player::input()
{
    if (!isLocal)
    {
        return;
    }

    camera->input();

    ui->input();
}

void Player::update(float dt)
{
    if (!isLocal)
    {
        return;
    }

    camera->update(dt);

    ui->update(dt);
}

void Player::output(Renderer *renderer)
{
    if (!isLocal)
    {
        return;
    }

    ui->output(renderer);
}

void Player::registerInputs()
{
    Controls *controls = Controls::getInstance();

    controls->mouseRightClickHandlers.push_back([this](Vector mousePosition)
                                                {
        if (ui->isMouseAbove()) {
            return;
        }

        interact(camera->toGlobal(mousePosition)); });
}

void Player::selectEntities(const SDL_FRect &rect)
{
    SDL_FRect globalRect = camera->toGlobal(rect);

    std::vector<Entity *> entities = map->getEntitiesInRect(globalRect);

    // Clear selected entities
    deselectAll();

    selectedEntities->clear();

    for (auto entity : entities)
    {
        selectedEntities->addMember(entity->id);
    }

    selectAll();
}

void Player::interact(Vector position)
{
    SDL_FRect rect = {position.x, position.y, 0, 0};

    std::vector<Entity *> entities = map->getEntitiesInRect(rect);

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
