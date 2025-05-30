#include <iostream>

#include "core/Renderer.hpp"
#include "fonts/8x8square_roguelike_ascii_font.h"

Renderer *Renderer::instancePtr = NULL;

const Vector Renderer::windowSize = {800, 600};

Renderer::Renderer()
{
    window = SDL_CreateWindow("CWars",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              int(windowSize.x), int(windowSize.y),
                              SDL_WINDOW_SHOWN);

    if (!window)
    {
        throw std::runtime_error("Failed to create window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        throw std::runtime_error("Failed to create renderer");
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

    loadFonts();
}

Renderer::~Renderer()
{
    cleanFonts();

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
}

Renderer *Renderer::getInstance()
{
    if (!instancePtr)
    {
        instancePtr = new Renderer();
    }

    return instancePtr;
}

void Renderer::deleteInstance()
{
    if (instancePtr)
    {
        delete instancePtr;
        instancePtr = NULL;
    }
}

void Renderer::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::present()
{
    SDL_RenderPresent(renderer);
}

void Renderer::loadFonts()
{
    SDL_RWops *defaultRWFont = SDL_RWFromConstMem(__8x8_square_roguelike_ascii_font_ttf, __8x8_square_roguelike_ascii_font_ttf_len);
    if (!defaultRWFont)
    {
        throw std::runtime_error("Failed to read font");
    }

    TTF_Font *defaultFont = TTF_OpenFontRW(defaultRWFont, 1, 24);

    fonts["default"] = defaultFont;

    SDL_RWops *unitRWFont = SDL_RWFromConstMem(__8x8_square_roguelike_ascii_font_ttf, __8x8_square_roguelike_ascii_font_ttf_len);
    if (!unitRWFont)
    {
        throw std::runtime_error("Failed to read font");
    }

    TTF_Font *unitFont = TTF_OpenFontRW(unitRWFont, 1, 16);

    fonts["unit"] = unitFont;
}

void Renderer::cleanFonts()
{
    for (auto &font : fonts)
    {
        TTF_CloseFont(font.second);
    }
}