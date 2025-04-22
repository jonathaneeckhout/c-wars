#include "engine/Camera.hpp"

Camera::Camera()
{
    name = "Camera";
}

Camera::~Camera() {}

void Camera::setActive(bool active)
{
    this->active = active;
}