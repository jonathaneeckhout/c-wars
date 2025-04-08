#include <iostream>
#include <csignal>
#include "Game.h"

using namespace std;

Game game;

void signalHandler(int signum)
{
    cout << "Interrupt signal (" << signum << ") received.\n";

    game.stop();
}

int main()
{
    std::signal(SIGINT, signalHandler);

    game.run();

    return 0;
}