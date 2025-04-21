#pragma once
#include <string>
#include <map>
#include <memory>
#include <SDL2/SDL.h>

#include "core/Controls.hpp"
#include "player/Camera.hpp"
#include "player/PlayerResources.hpp"
#include "entities/Entity.hpp"
#include "player/Group.hpp"
#include "core/Renderer.hpp"
#include "ui/menus/WorkerMenu.hpp"

// Forward declare classes to avoid circular include
class Map;
class UI;

class Player
{
public:
    std::string name = "";
    Map *map = NULL;
    bool isLocal = false;

    Camera *camera = NULL;
    UI *ui = NULL;

    PlayerResources resources;

    Player(std::string name, Map *map, bool isLocal);
    ~Player();

    void input();
    void update(float dt);
    void output(Renderer *renderer);

    void selectEntities(const SDL_FRect &rect);
    void interact(Vector position);

private:
    Group *selectedEntities = NULL;

    void registerInputs();

    void selectAll();
    void deselectAll();
};