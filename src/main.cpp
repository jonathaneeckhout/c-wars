#include <iostream>
#include <csignal>

#include "engine/core/Game.hpp"

#include "game/fonts/8x8square_roguelike_ascii_font.h"

#include "game/maps/Moon.hpp"

Game *game = NULL;

static void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

    game->stop();
}

static void loadResources()
{
    Resources *resources = Resources::getInstance();

    resources->loadFont("default", __8x8_square_roguelike_ascii_font_ttf, __8x8_square_roguelike_ascii_font_ttf_len);
}

static void populateGame()
{
    Moon *moon = new Moon();
    game->addChild(moon);
}

int main()
{
    game = Game::getInstance();

    std::signal(SIGINT, signalHandler);

    loadResources();

    populateGame();

    game->run();

    Game::deleteInstance();

    return 0;
}