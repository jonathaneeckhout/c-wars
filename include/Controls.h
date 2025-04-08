#pragma once

#include <SDL2/SDL.h>
#include <functional>

#include "utils/Vector.h"

class Controls
{
public:
    std::function<void()> onStop = NULL;
    std::function<void(Vector)> onMoveCamera = NULL;

    Controls();
    ~Controls();
    void input();

private:
    bool wPressed = false;
    bool sPressed = false;
    bool aPressed = false;
    bool dPressed = false;

    void handleCameraMovement();
};