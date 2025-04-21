#pragma once

#include "core/Renderer.hpp"
#include "player/Player.hpp"
#include "player/ui/Selection.hpp"

class UI
{
public:
    UI(Player *player);
    ~UI();

    void input();
    void update(float dt);
    void output(Renderer *renderer);

    void showWorkerMenu();
    void hideWorkerMenu();

    void closeAllMenus();

    bool isMouseAbove() { return mouseIsAbove; }

private:
    Player *player = NULL;

    bool mouseIsAbove = false;

    Selection selection;

    WorkerMenu workerMenu;

    void drawResources(Renderer *renderer, Vector offset);

    void checkMouseAbove(Vector mousePosition);
};
