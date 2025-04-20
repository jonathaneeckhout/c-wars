#include "player/ui/UI.hpp"

UI::UI(Player *player) : player(player) {}

UI::~UI() {}

void UI::input() {}

void UI::update(float) {}

void UI::output(Renderer *renderer)
{
    drawResources(renderer, {0, 0});
}

void UI::drawResources(Renderer *renderer, Vector offset)
{
    SDL_Color textColor = {255, 255, 255, 255};

    std::string resourcesString = "Metal: " + std::to_string(static_cast<int>(player->resources.metal));

    SDL_Surface *textSurface = TTF_RenderText_Solid(renderer->fonts["unit"], resourcesString.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer->renderer, textSurface);

    SDL_FRect textRect = {offset.x, offset.y, float(textSurface->w), float(textSurface->h)};
    SDL_RenderCopyF(renderer->renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}