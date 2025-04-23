#include "engine/Camera.hpp"

Camera *Camera::current = nullptr;

Camera::Camera(Vector position) : Entity(position)
{
    name = "Camera";
}

Camera::~Camera() {}

Camera *Camera::getCurrent()
{
    return current;
}

void Camera::setActive(bool active)
{
    this->active = active;

    if (active)
    {
        if (current != nullptr)
        {
            current->active = false;
        }
        current = this;
    }
    else
    {
        if (current == this)
        {
            current = nullptr;
        }
    }
}