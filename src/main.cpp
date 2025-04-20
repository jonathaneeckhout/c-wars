#include <iostream>
#include <csignal>

#include "core/Game.hpp"

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