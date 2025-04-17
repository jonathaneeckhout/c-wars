#pragma once

#include "utils/Vector.hpp"

class Camera
{
public:
    Vector position = {0, 0};
    Vector velocity = {0, 0};
    float speed = 500.0f;

    Camera();
    ~Camera();

    void input();
    void update(float dt);
    void move(Vector direction);
};