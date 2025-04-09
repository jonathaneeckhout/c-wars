#include "Camera.h"
#include <iostream>

Camera::Camera() {}

Camera::~Camera() {}

void Camera::input()
{
}

void Camera::update(float dt)
{
    position += velocity * speed * dt;

    // std::cout << position.x << " " << position.y << std::endl;
}

void Camera::move(Vector direction)
{
    velocity = direction;
}