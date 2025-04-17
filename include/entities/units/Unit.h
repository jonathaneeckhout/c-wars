#pragma once

#include <string>

#include "entities/Entity.h"
#include "entities/resources/Resource.h"

enum class UnitState
{
    Idle,
    Moving,
    Gathering,
    Attacking,
    Building
};

class Unit : public Entity
{
    const int arrivalRadius = 10;

public:
    std::string player = "";
    const Vector size = {32, 32};
    Vector velocity = {0, 0};

    float speed = 100.0f;
    float interactionRange = 64.0f;

    Vector targetPosition = {0, 0};
    std::string targetID = "";

    UnitState state = UnitState::Idle;

    Unit(std::string id, std::string player, Map *map, Vector position);
    ~Unit();

    void update(float dt) override;
    void output(Renderer *renderer, Camera *camera) override;

    void select();
    void deselect();

    void move(Vector position);
    void interact(std::string target);

    Entity *getTargetEntity();
    Resource *getTargetResource();

private:
    void handleMoveUpdate(float dt);
    void handleInteractUpdate(float dt);

    virtual void handleResourceUpdate(Resource *resource, float dt);

    void drawName(Renderer *renderer, Vector position, Vector offset);
    void drawPlayer(Renderer *renderer, Vector position, Vector offset);
    void drawState(Renderer *rendered, Vector position, Vector offset);
};