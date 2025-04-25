#include "engine/ui/text/Label.hpp"
#include "engine/core/Renderer.hpp"

#include <iostream>

Label::Label(Vector position, const std::string &text) : Text(position, text)
{
    name = "Label";
}

Label::~Label() {}

void Label::output()
{
    Renderer *renderer = Renderer::getInstance();

    SDL_FRect rect = {position.x - float(surface->w) / 2, position.y, float(surface->w), float(surface->h)};
    SDL_RenderCopyF(renderer->renderer, texture, NULL, &rect);
}