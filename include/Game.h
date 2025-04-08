#pragma once
#include <atomic>
#include <string>
#include <map>
#include <SDL2/SDL.h>

#include "Controls.h"
#include "Camera.h"
#include "Entity.h"

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

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::atomic<bool> running;
    std::map<std::string, Entity *> entities;
    void input();
    void update(float dt);
    void output();
    void registerInputs();
};