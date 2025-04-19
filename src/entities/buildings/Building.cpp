#include "entities/buildings/Building.hpp"
#include "maps/Map.hpp"

Building::Building(std::string id, std::string player, Map *map, Vector position) : Entity(id, map, position), player(player) {}

Building::~Building() {}

void Building::update(float) {}

void Building::output(Renderer *renderer)
{
    SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_NONE);

    Vector renderPostion = position - renderer->currentCamera->position;

    Vector buildingRenderPosition = renderPostion - renderOffset;

    // Draw selected area
    if (selected)
    {
        SDL_FRect selectedSquare = {buildingRenderPosition.x - selectedRenderOffset.x, buildingRenderPosition.y - selectedRenderOffset.y, selectedSize.x, selectedSize.y};
        SDL_SetRenderDrawColor(renderer->renderer, selectColor.r, selectColor.g, selectColor.b, selectColor.a);
        SDL_RenderFillRectF(renderer->renderer, &selectedSquare);
    }

    // Draw Resource
    SDL_FRect square = {buildingRenderPosition.x, buildingRenderPosition.y, size.x, size.y};
    SDL_SetRenderDrawColor(renderer->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRectF(renderer->renderer, &square);

    drawName(renderer, renderPostion, Vector{0, -48});
    drawPlayer(renderer, renderPostion, Vector{0, -64});

    SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_ADD);
}

void Building::store(std::pair<std::string, float> goods)
{
    Player *player = map->getPlayer(this->player);
    if (player == nullptr)
    {
        return;
    }

    player->resources.add(goods);
}

void Building::drawPlayer(Renderer *renderer, Vector position, Vector offset)
{
    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Surface *textSurface = TTF_RenderText_Solid(renderer->fonts["unit"], player.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer->renderer, textSurface);

    SDL_FRect textRect = {position.x - float(textSurface->w) / 2 + offset.x, position.y + offset.y, float(textSurface->w), float(textSurface->h)};
    SDL_RenderCopyF(renderer->renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}