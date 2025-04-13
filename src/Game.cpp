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

    map.name = "TestMap";

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

    registerInputs();

    // Debugging, remove later
    std::string id = map.addEntity("Worker", "TestPlayer", Vector(100, 100));
    std::cout << "Entity ID after adding: " << id << std::endl;

    std::string id2 = map.addEntity("Worker", "TestPlayer", Vector(180, 180));
    std::cout << "Entity ID after adding: " << id2 << std::endl;
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

    controls.onSelection = [this](SDL_FRect rect)
    {
        SDL_FRect globalRect = rect;
        globalRect.x += camera.position.x;
        globalRect.y += camera.position.y;
        player->scanEntities(globalRect, map.getEntities());
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

    controls.output(renderer, &camera);

    map.output(renderer, &camera);

    SDL_RenderPresent(renderer);
}

void Game::update(float dt)
{
    camera.update(dt);

    map.update(dt);
}

void Game::setPlayer(Player *player)
{
    this->player = player;
}
