#include "player/Camera.hpp"

Camera::Camera() {}

Camera::~Camera() {}

void Camera::input()
{
}

void Camera::update(float dt)
{
    position += velocity * speed * dt;
}

void Camera::move(Vector direction)
{
    velocity = direction;
}