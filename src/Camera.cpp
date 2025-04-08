#include "Camera.h"
#include <iostream>

Camera::Camera() {}

Camera::~Camera() {}

void Camera::input()
{
}

void Camera::update(float dt)
{
    this->position += this->velocity * this->speed * dt;

    // std::cout << this->position.x << " " << this->position.y << std::endl;
}

void Camera::move(Vector direction)
{
    this->velocity = direction;
}