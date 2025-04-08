#include "Controls.h"
#include <iostream>

Controls::Controls() {}

Controls::~Controls() {}

void Controls::input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            if (this->onStop != NULL)
            {
                this->onStop();
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                if (this->onStop != NULL)
                {
                    this->onStop();
                }
                break;

            case SDLK_w:
                this->wPressed = true;
                break;

            case SDLK_s:
                this->sPressed = true;
                break;

            case SDLK_a:
                this->aPressed = true;
                break;

            case SDLK_d:
                this->dPressed = true;
                break;

            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                this->wPressed = false;
                break;
            case SDLK_s:
                this->sPressed = false;
                break;
            case SDLK_a:
                this->aPressed = false;
                break;
            case SDLK_d:
                this->dPressed = false;
                break;
            default:
                break;
            }

            break;
        default:
            break;
        }

        this->handleCameraMovement();
    }
}

void Controls::handleCameraMovement()
{
    Vector cameraMoveDirection = {0, 0};

    if (this->wPressed)
    {
        cameraMoveDirection.y -= 1;
    }
    if (this->sPressed)
    {
        cameraMoveDirection.y += 1;
    }
    if (this->aPressed)
    {
        cameraMoveDirection.x -= 1;
    }
    if (this->dPressed)
    {
        cameraMoveDirection.x += 1;
    }

    if (this->onMoveCamera != NULL)
    {
        this->onMoveCamera(cameraMoveDirection.normalize());
    }
}
