#include <iostream>
#include <csignal>

#include "engine/core/Game.hpp"

Game *game = NULL;

static void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

    game->stop();
}

static void populateGame()
{
    Object *players = new Object();
    players->name = "Players";
    game->addChild(players);
}

int main()
{
    game = Game::getInstance();

    std::signal(SIGINT, signalHandler);

    populateGame();

    game->run();

    Game::deleteInstance();

    return 0;
}