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

    void selectEntities(std::vector<Entity *> entities);
    void interact(Vector position, std::vector<Entity *> entities);

private:
    Group *selectedEntities = NULL;

    std::unique_ptr<WorkerMenu> workerMenu;

    void registerInputs();

    void selectAll();
    void deselectAll();

    // TODO: move these to UI
    void checkWhichMenu();
    void closeAllMenus();
};