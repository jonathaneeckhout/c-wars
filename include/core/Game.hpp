#pragma once
#include <atomic>
#include <string>
#include <map>

#include "core/Renderer.hpp"
#include "maps/Map.hpp"
#include "player/Player.hpp"

class Game
{

public:
    ~Game();

    // Delete copy constructor
    Game(const Game &) = delete;

    static Game *getInstance();
    static void deleteInstance();

    void run();
    void stop();

    Map *getMap() { return map; }

private:
    static Game *instancePtr;

    float fps = 30.0f;

    std::atomic<bool> running;

    Renderer *renderer;
    Controls *controls = NULL;

    Map *map = NULL;

    Game();

    void input();
    void update(float dt);
    void output();
};