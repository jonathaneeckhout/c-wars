#pragma once

#include "core/Renderer.hpp"
#include "player/Player.hpp"

class UI
{
public:
    UI(Player *player);
    ~UI();

    void input();
    void update(float dt);
    void output(Renderer *renderer);

private:
    Player *player = NULL;

    void drawResources(Renderer *renderer, Vector offset);
};
