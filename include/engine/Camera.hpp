#pragma once

#include "engine/Object.hpp"

class Camera : public Object
{
public:
    Camera();
    ~Camera();

    void setActive(bool active);

private:
    bool active = false;
};