#include <chrono>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>

#include "Game.h"
#include "maps/Moon.h"

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

    map = new Moon();

    registerInputs();
}

Game::~Game()
{
    delete map;

    delete renderer;

    TTF_Quit();

    SDL_Quit();
}

void Game::registerInputs()
{
    controls.onStop = [this]()
    { stop(); };

    controls.onMoveCamera = [this](Vector direction)
    {
        camera.move(direction);
    };

    controls.onSelection = [this](SDL_FRect rect)
    {
        SDL_FRect globalRect = rect;
        globalRect.x += camera.position.x;
        globalRect.y += camera.position.y;

        std::vector<Entity *> entities = map->getEntitiesInRect(globalRect);

        player->selectEntities(entities);
    };

    controls.onInteract = [this](Vector position)
    {
        Vector globalPosition = position;
        globalPosition.x += camera.position.x;
        globalPosition.y += camera.position.y;

        SDL_FRect globalRect = {globalPosition.x, globalPosition.y, 0, 0};

        std::vector<Entity *> entities = map->getEntitiesInRect(globalRect);

        player->interact(globalPosition, entities);
    };
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
    controls.input();
}

void Game::output()
{
    renderer->clear();

    controls.output(renderer, &camera);

    map->output(renderer, &camera);

    renderer->present();
}

void Game::update(float dt)
{
    camera.update(dt);

    map->update(dt);
}

void Game::setPlayer(Player *player)
{
    this->player = player;
}
