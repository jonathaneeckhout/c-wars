#pragma once
#include <string>
#include <map>
#include <SDL2/SDL.h>

#include "player/Controls.hpp"
#include "player/Camera.hpp"
#include "player/PlayerResources.hpp"
#include "entities/Entity.hpp"
#include "player/Group.hpp"
#include "Renderer.hpp"

// Forward declare Map to avoid circular include
class Map;

class Player
{
public:
    std::string name = "";
    Map *map = NULL;
    bool isLocal = false;

    Controls *controls = NULL;
    Camera *camera = NULL;

    PlayerResources resources;

    Player(std::string name, Map *map, bool isLocal, Renderer *renderer);
    ~Player();

    void input();
    void update(float dt);
    void output(Renderer *renderer);

    void selectEntities(std::vector<Entity *> entities);
    void interact(Vector position, std::vector<Entity *> entities);

private:
    Group *selectedEntities = NULL;

    void registerInputs();

    void selectAll();
    void deselectAll();

    void drawResources(Renderer *renderer, Vector offset);
};