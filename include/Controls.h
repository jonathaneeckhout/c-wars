#pragma once

#include <SDL2/SDL.h>
#include <functional>

#include "utils/Vector.h"
#include "Renderer.h"
#include "Camera.h"
#include "Selection.h"

class Controls
{
public:
    std::function<void()> onStop = NULL;
    std::function<void(Vector)> onMoveCamera = NULL;
    std::function<void(SDL_FRect)> onSelection = NULL;
    std::function<void(Vector)> onInteract = NULL;

    Controls();
    ~Controls();
    void input();
    void update(float dt);
    void output(Renderer *renderer, Camera *camera);

private:
    bool wPressed = false;
    bool sPressed = false;
    bool aPressed = false;
    bool dPressed = false;

    Selection selection;

    void handleCameraMovement();
};