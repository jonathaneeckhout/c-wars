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
    Player *player = new Player("TestPlayer");
    game.setPlayer(player);
    player->setMap(game.getMap());

    game.run();

    delete player;

    return 0;
}