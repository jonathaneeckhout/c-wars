#include <iostream>
#include <signal.h>

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

    workerMenu = std::make_unique<WorkerMenu>();

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

    closeAllMenus();

    selectedEntities->clear();

    for (auto entity : entities)
    {
        selectedEntities->addMember(entity->id);
    }

    selectAll();

    checkWhichMenu();
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

void Player::checkWhichMenu()
{
    if (selectedEntities->getMembers().size() == 0)
    {
        return;
    }

    Worker *worker = dynamic_cast<Worker *>(map->getEntity(selectedEntities->getMembers()[0]));
    if (worker)
    {
        workerMenu->visible = true;
        return;
    }
}

void Player::closeAllMenus()
{
    workerMenu->visible = false;
}