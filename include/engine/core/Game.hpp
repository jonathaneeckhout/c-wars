#pragma once
#include <atomic>
#include <string>

#include "engine/Object.hpp"
#include "engine/core/Renderer.hpp"
#include "engine/core/Controls.hpp"
#include "engine/core/Resources.hpp"

class Game : public Object
{

public:
    ~Game();

    // Delete copy constructor
    Game(const Game &) = delete;

    static Game *getInstance();
    static void deleteInstance();

    void run();
    void stop();

private:
    static Game *instancePtr;

    float fps = 30.0f;

    std::atomic<bool> running;

    Renderer *renderer = NULL;
    Controls *controls = NULL;
    Resources *resources = NULL;

    Game();

    void input() override;
    void update(float dt) override;
    void output() override;
};