#pragma once

#include <string>
#include <SDL2/SDL_ttf.h>

#include "engine/ui/UI.hpp"

class Text : public UI
{
public:
    std::string text = "";

    unsigned int size = 16;

    bool centered = false;

    SDL_Color color = {255, 255, 255, 255};

    Text(Vector position, const std::string &text);
    ~Text();

    bool setFont(const std::string &name, unsigned int size);

protected:
    TTF_Font *font = nullptr;

    SDL_Surface *surface = nullptr;

    SDL_Texture *texture = nullptr;
};