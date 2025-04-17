#pragma once
#include <atomic>
#include <string>
#include <map>

#include "Renderer.hpp"
#include "Controls.hpp"
#include "Camera.hpp"
#include "maps/Map.hpp"
#include "Player.hpp"

class Game
{
public:
    float fps = 30.0f;

    Controls controls;
    Camera camera;

    Game();
    ~Game();
    void run();
    void stop();

    Map *getMap() { return map; }

    void setPlayer(Player *player);

private:
    Renderer *renderer;

    std::atomic<bool> running;

    Map *map = NULL;
    std::map<std::string, Player *> players;

    Player *player;

    void input();
    void update(float dt);
    void output();
    void registerInputs();
};