#pragma once
#include <atomic>
#include <string>
#include <map>

#include "Renderer.h"
#include "Controls.h"
#include "Camera.h"
#include "maps/Map.h"
#include "Player.h"

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

    Map *getMap() { return &map; }

    void setPlayer(Player *player);

private:
    Renderer *renderer;

    std::atomic<bool> running;

    Map map;
    std::map<std::string, Player *> players;

    Player *player;

    void input();
    void update(float dt);
    void output();
    void registerInputs();
};