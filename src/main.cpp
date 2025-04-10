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

    // For now we just create a test player
    Player player;
    player.name = "TestPlayer";
    game.setPlayer(player);

    game.run();

    return 0;
}