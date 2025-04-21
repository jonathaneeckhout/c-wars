#include <iostream>
#include "player/ui/UI.hpp"

UI::UI(Player *player) : player(player)
{
    Controls *controls = Controls::getInstance();

    controls->mouseLeftClickHandlers.push_back([this](Vector mousePosition)
                                               {
        if (isMouseAbove())
        {
            return;
        }
        selection.start(mousePosition); });

    controls->mouseLeftReleaseHandlers.push_back([this](Vector mousePosition)
                                                 { 
                                                    selection.end(mousePosition); 
                                                    const SDL_FRect selectionRect = selection.getSelectionRect(); 
                                                    this->player->selectEntities(selectionRect); });

    controls->mouseMovementHandlers.push_back([this](Vector mousePosition)
                                              { 
                                                checkMouseAbove(mousePosition); 
                                                selection.move(mousePosition); });
}

UI::~UI() {}

void UI::input()
{
    workerMenu.input();
}

void UI::update(float dt)
{
    workerMenu.update(dt);

    if (mouseIsAbove)
    {
        std::cout << "Mouse is above UI" << std::endl;
    }
}

void UI::output(Renderer *renderer)
{
    drawResources(renderer, {0, 0});

    selection.output(renderer);

    workerMenu.output(renderer);
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

void UI::closeAllMenus()
{
    workerMenu.visible = false;
}

void UI::showWorkerMenu()
{
    workerMenu.visible = true;
}

void UI::hideWorkerMenu()
{
    workerMenu.visible = false;
}

void UI::checkMouseAbove(Vector mousePosition)
{
    mouseIsAbove = workerMenu.isMouseAbove(mousePosition);
    if (mouseIsAbove)
    {
        return;
    }

    mouseIsAbove = false;
}