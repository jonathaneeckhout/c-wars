#pragma once
#include <atomic>
#include <string>
#include <map>

#include "Renderer.hpp"
#include "maps/Map.hpp"
#include "player/Player.hpp"

class Game
{
private:
    float fps = 30.0f;

    Renderer *renderer;

    std::atomic<bool> running;

    Map *map = NULL;

    static Game *instancePtr;

    Game();

    void input();
    void update(float dt);
    void output();

public:
    ~Game();

    // Delete copy constructor
    Game(const Game &obj) = delete;

    static Game *getInstance();
    static void deleteInstance();

    void run();
    void stop();

    Map *getMap() { return map; }
};