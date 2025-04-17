#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>

#include "player/Camera.hpp"

class Renderer
{
public:
    SDL_Window *window;
    SDL_Renderer *renderer;

    Camera *currentCamera = NULL;

    std::map<std::string, TTF_Font *> fonts;

    Renderer();
    ~Renderer();

    void clear();
    void present();

private:
    void loadFonts();
    void cleanFonts();
};