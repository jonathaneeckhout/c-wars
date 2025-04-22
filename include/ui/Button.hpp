#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "utils/Vector.hpp"

class Button
{
public:
    std::string text = "";

    Button();
    ~Button();

    void setPosition(const Vector &location);

private:
    Vector position;
    Vector size;
    SDL_FRect rect;
};