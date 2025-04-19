#include <iostream>
#include <csignal>

#include "Game.hpp"

Game *Game::instancePtr = NULL;

Game *game = NULL;

void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

    game->stop();
}

int main()
{
    game = Game::getInstance();

    std::signal(SIGINT, signalHandler);

    game->run();

    Game::deleteInstance();

    return 0;
}