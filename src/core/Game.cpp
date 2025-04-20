#include <chrono>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>

#include "core/Game.hpp"
#include "maps/Moon.hpp"

Game *Game::instancePtr = NULL;

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

    renderer = Renderer::getInstance();

    controls = Controls::getInstance();

    controls->onStop = [this]()
    {
        stop();
    };

    map = new Moon();
}

Game::~Game()
{
    delete map;

    Controls::deleteInstance();

    Renderer::deleteInstance();

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

    const auto frameDuration = std::chrono::duration<double>(1.0 / fps);

    while (running)
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        input();

        update(frameDuration.count());

        output();

        auto frameEnd = std::chrono::high_resolution_clock::now();

        auto elapsed = frameEnd - frameStart;

        if (elapsed < frameDuration)
        {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
    }
}

void Game::stop()
{
    running = false;
}

void Game::input()
{
    controls->input();

    map->input();
}

void Game::update(float dt)
{
    controls->update(dt);

    map->update(dt);
}

void Game::output()
{
    renderer->clear();

    controls->output(renderer);

    map->output(renderer);

    renderer->present();
}
