#include <chrono>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>

#include "Game.hpp"
#include "maps/Moon.hpp"

Game::Game() : running(false)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error("Failed to initialize SDL");
    }

    if (TTF_Init() < 0)
    {
        throw std::runtime_error("Failed to initialize TFF");
    }

    renderer = new Renderer();

    map = new Moon(renderer);
}

Game::~Game()
{
    delete map;

    delete renderer;

    TTF_Quit();

    SDL_Quit();
}

Game *Game::getInstance()
{
    if (instancePtr == NULL)
    {
        instancePtr = new Game();
    }

    return instancePtr;
}

void Game::deleteInstance()
{
    if (instancePtr != NULL)
    {
        delete instancePtr;
        instancePtr = NULL;
    }
}

void Game::run()
{
    running = true;

    const double frameDuration = 1.0 / fps;

    while (running)
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        input();

        update(static_cast<float>(frameDuration));

        output();

        auto frameEnd = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = frameEnd - frameStart;
        double duration = elapsed.count();

        double sleepTime = frameDuration - duration;

        if (sleepTime > 0.0)
        {
            SDL_Delay(sleepTime * 1000.0);
        }
    }
}

void Game::stop()
{
    running = false;
}

void Game::input()
{
    map->input();
}

void Game::update(float dt)
{
    map->update(dt);
}

void Game::output()
{
    renderer->clear();

    map->output(renderer);

    renderer->present();
}
