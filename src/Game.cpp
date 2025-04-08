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

    this->registerInputs();

    //Debug line: add one test worker
    Worker *worker = new Worker(Vector(100, 100));
    this->entities["worker"] = worker;
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::registerInputs()
{
    this->controls.onStop = [this]()
    { this->stop(); };

    this->controls.onMoveCamera = [this](Vector direction)
    {
        this->camera.move(direction);
    };
}

void Game::run()
{
    this->running = true;

    const double frameDuration = 1.0 / this->fps;

    while (this->running)
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        this->input();

        this->update(static_cast<float>(frameDuration));

        this->output();

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
    this->running = false;
}

void Game::input()
{
    this->controls.input();
}

void Game::output()
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);

    for (auto entity : this->entities)
    {
        entity.second->output(this->renderer, &this->camera);
    }

    SDL_RenderPresent(this->renderer);
}

void Game::update(float dt)
{
    this->camera.update(dt);

    for (auto entity : this->entities)
    {
        entity.second->update(dt);
    }
}
