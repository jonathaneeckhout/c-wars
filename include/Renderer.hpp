#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>

class Renderer
{
public:
    SDL_Window *window;
    SDL_Renderer *renderer;

    std::map<std::string, TTF_Font *> fonts;

    Renderer();
    ~Renderer();

    void clear();
    void present();

private:
    void loadFonts();
    void cleanFonts();
};