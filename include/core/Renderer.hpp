#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>

#include "utils/Vector.hpp"
#include "player/Camera.hpp"

class Renderer
{
public:
    SDL_Window *window;
    static const Vector windowSize;

    SDL_Renderer *renderer;

    Camera *currentCamera = NULL;

    std::map<std::string, TTF_Font *> fonts;

    ~Renderer();

    Renderer(const Renderer &) = delete;

    static Renderer *getInstance();
    static void deleteInstance();

    void clear();
    void present();

private:
    static Renderer *instancePtr;

    Renderer();

    void loadFonts();
    void cleanFonts();
};