#include "entities/Entity.hpp"

Entity::Entity(std::string id, Map *map, Vector position) : id(id), map(map), position(position) {}

Entity::~Entity() {}

void Entity::drawName(Renderer *renderer, Vector position, Vector offset)
{
    if (name.empty())
    {
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Surface *textSurface = TTF_RenderText_Solid(renderer->fonts["unit"], name.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer->renderer, textSurface);

    SDL_FRect textRect = {position.x - float(textSurface->w) / 2 + offset.x, position.y + offset.y, float(textSurface->w), float(textSurface->h)};
    SDL_RenderCopyF(renderer->renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}