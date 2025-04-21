#include "player/Camera.hpp"
#include "core/Controls.hpp"

Camera::Camera()
{
    Controls *controls = Controls::getInstance();

    controls->keyPressHandlers.push_back([this](std::string key)
                                         { 
        if (key == moveLeftKey) {
            moveLeft = true;
        } else if (key == moveRightKey) {
            moveRight = true;
        } else if (key == moveUpKey) {
            moveUp = true;
        } else if (key == moveDownKey) {
            moveDown = true;
        } });
    controls->keyReleaseHandlers.push_back([this](std::string key)
                                           { 
        if (key == moveLeftKey) {
            moveLeft = false;
        } else if (key == moveRightKey) {
            moveRight = false;
        } else if (key == moveUpKey) {
            moveUp = false;
        } else if (key == moveDownKey) {
            moveDown = false;
        } });
}

Camera::~Camera() {}

void Camera::input()
{
    Vector cameraMoveDirection = {0, 0};

    if (moveLeft)
    {
        cameraMoveDirection.x -= 1;
    }
    if (moveRight)
    {
        cameraMoveDirection.x += 1;
    }

    if (moveUp)
    {
        cameraMoveDirection.y -= 1;
    }
    if (moveDown)
    {
        cameraMoveDirection.y += 1;
    }

    velocity = cameraMoveDirection.normalize();
}

void Camera::update(float dt)
{
    position += velocity * speed * dt;
}

Vector Camera::toGlobal(Vector point)
{
    Vector globalPosition = point;
    globalPosition.x += position.x;
    globalPosition.y += position.y;

    return globalPosition;
}

SDL_FRect Camera::toGlobal(SDL_FRect rect)
{
    SDL_FRect globalRect = rect;
    globalRect.x += position.x;
    globalRect.y += position.y;

    return globalRect;
}
