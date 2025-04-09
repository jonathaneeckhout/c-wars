#include <chrono>
#include <thread>
#include <iostream> // needed for std::cerr
#include "Game.h"

#include "entities/Worker.h"

Game::Game() : window(nullptr), renderer(nullptr), running(false)
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error("Failed to initialize SDL");
    }

    window = SDL_CreateWindow("CWars",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800, 600,
                              SDL_WINDOW_SHOWN);

    if (!window)
    {
        throw std::runtime_error("Failed to create window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        throw std::runtime_error("Failed to create renderer");
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

    registerInputs();

    // Debug line: add one test worker
    Worker *worker = new Worker(Vector(100, 100));
    entities["worker"] = worker;
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (auto entity : entities)
    {
        entity.second->output(renderer, &camera);
    }

    controls.output(renderer, &camera);

    SDL_RenderPresent(renderer);
}

void Game::update(float dt)
{
    camera.update(dt);

    for (auto entity : entities)
    {
        entity.second->update(dt);
    }
}
