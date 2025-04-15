#include "Controls.h"
#include <iostream>

Controls::Controls()
{
    selection.onSelection = [this](SDL_FRect rect)
    {
        if (onSelection != NULL)
        {
            onSelection(rect);
        }
    };
}

Controls::~Controls() {}

void Controls::input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            if (onStop != NULL)
            {
                onStop();
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                if (onStop != NULL)
                {
                    onStop();
                }
                break;

            case SDLK_w:
                wPressed = true;
                break;

            case SDLK_s:
                sPressed = true;
                break;

            case SDLK_a:
                aPressed = true;
                break;

            case SDLK_d:
                dPressed = true;
                break;

            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                wPressed = false;
                break;
            case SDLK_s:
                sPressed = false;
                break;
            case SDLK_a:
                aPressed = false;
                break;
            case SDLK_d:
                dPressed = false;
                break;
            default:
                break;
            }

            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                selection.start(Vector{float(event.button.x), float(event.button.y)});
                break;
            case SDL_BUTTON_RIGHT:
                if (onInteract != NULL)
                {
                    onInteract(Vector{float(event.button.x), float(event.button.y)});
                }
                break;
            case SDL_BUTTON_MIDDLE:
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                selection.end(Vector{float(event.button.x), float(event.button.y)});

                break;
            case SDL_BUTTON_RIGHT:
                break;
            case SDL_BUTTON_MIDDLE:
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            selection.move(Vector{float(event.motion.x), float(event.motion.y)});

            break;
        default:
            break;
        }

        handleCameraMovement();
    }
}

void Controls::handleCameraMovement()
{
    Vector cameraMoveDirection = {0, 0};

    if (wPressed)
    {
        cameraMoveDirection.y -= 1;
    }
    if (sPressed)
    {
        cameraMoveDirection.y += 1;
    }
    if (aPressed)
    {
        cameraMoveDirection.x -= 1;
    }
    if (dPressed)
    {
        cameraMoveDirection.x += 1;
    }

    if (onMoveCamera != NULL)
    {
        onMoveCamera(cameraMoveDirection.normalize());
    }
}

void Controls::update(float) {}

void Controls::output(Renderer *renderer, Camera *camera)
{
    selection.output(renderer, camera);
}