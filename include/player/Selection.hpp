#pragma once

#include <SDL2/SDL.h>
#include <functional>

#include "utils/Vector.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

class Selection
{
public:
    std::function<void(SDL_FRect)> onSelection = NULL;

    Selection();
    ~Selection();

    void start(Vector position);
    void move(Vector position);
    void end(Vector position);

    void output(Renderer *renderer, Camera *camera);

private:
    bool selected = false;
    Vector startPos = {0, 0};
    Vector endPos = {0, 0};

    SDL_FRect getSelectionRect() const;
};