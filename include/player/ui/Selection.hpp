#pragma once

#include <SDL2/SDL.h>

#include "utils/Vector.hpp"
#include "core/Renderer.hpp"

class Selection
{
public:
    Selection();
    ~Selection();

    void output(Renderer *renderer);

    void start(Vector position);
    void move(Vector position);
    void end(Vector position);
    SDL_FRect getSelectionRect() const;

private:
    bool selected = false;
    Vector startPos = {0, 0};
    Vector endPos = {0, 0};
};