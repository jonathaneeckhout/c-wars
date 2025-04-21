#pragma once
#include <SDL2/SDL.h>
#include <string>

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

    Vector toGlobal(Vector point);
    SDL_FRect toGlobal(SDL_FRect rect);

private:
    const std::string moveLeftKey = "A";
    const std::string moveRightKey = "D";
    const std::string moveUpKey = "W";
    const std::string moveDownKey = "S";

    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    void handleCameraMovement();
};