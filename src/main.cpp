#include <iostream>
#include <csignal>

#include "Game.hpp"

Game game;

void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

    game.stop();
}

int main()
{
    std::signal(SIGINT, signalHandler);

    game.run();

    return 0;
}