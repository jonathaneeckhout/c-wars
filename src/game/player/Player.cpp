#include "game/player/Player.hpp"

Player::Player(const std::string &name)
{
    this->name = name;
}

Player::Player(const std::string &name, const bool &isLocal)
{
    this->name = name;
    this->isLocal = isLocal;

    if (!isLocal)
    {
        return;
    }

    camera = new Camera();
    this->addChild(camera);
    camera->setActive(true);
}

Player::~Player() {}
