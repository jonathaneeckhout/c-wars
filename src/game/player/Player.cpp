#include "game/player/Player.hpp"

Player::Player(const std::string &name) : Entity(Vector(0, 0))
{
    this->name = name;
}

Player::Player(const std::string &name, const bool &isLocal) : Entity(Vector(0, 0))
{
    this->name = name;
    this->isLocal = isLocal;

    if (!isLocal)
    {
        return;
    }

    camera = new Camera(position);
    this->addChild(camera);
    camera->setActive(true);
}

Player::~Player() {}
