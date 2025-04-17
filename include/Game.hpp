#pragma once
#include <atomic>
#include <string>
#include <map>

#include "Renderer.hpp"
#include "maps/Map.hpp"
#include "player/Player.hpp"

class Game
{
public:
    float fps = 30.0f;

    Game();
    ~Game();
    void run();
    void stop();

    Map *getMap() { return map; }

private:
    Renderer *renderer;

    std::atomic<bool> running;

    Map *map = NULL;

    void input();
    void update(float dt);
    void output();
};