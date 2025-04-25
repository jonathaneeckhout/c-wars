#pragma once

#include "engine/entities/Entity.hpp"

class Camera : public Entity
{
public:
    Camera(Vector position);
    ~Camera();

    static Camera *getCurrent();

    void setActive(bool active);

private:
    static Camera *current;

    bool active = false;
};