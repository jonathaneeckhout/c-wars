#pragma once

#include <SDL2/SDL.h>
#include <functional>

#include "utils/Vector.hpp"
#include "core/Renderer.hpp"
#include "player/ui/Selection.hpp"

class Controls
{
public:
    std::function<void()> onStop = NULL;
    std::function<void(Vector)> onMoveCamera = NULL;
    std::function<void(SDL_FRect)> onSelection = NULL;
    std::function<void(Vector)> onInteract = NULL;

    ~Controls();

    // Delete copy constructor
    Controls(const Controls &) = delete;

    static Controls *getInstance();
    static void deleteInstance();

    void input();
    void update(float dt);
    void output(Renderer *renderer);

private:
    static Controls *instancePtr;

    bool wPressed = false;
    bool sPressed = false;
    bool aPressed = false;
    bool dPressed = false;

    Selection selection;

    Controls();

    void handleCameraMovement();
};