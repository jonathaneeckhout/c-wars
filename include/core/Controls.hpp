#pragma once

#include <SDL2/SDL.h>
#include <functional>

#include "utils/Vector.hpp"
#include "core/Renderer.hpp"

class Controls
{
public:
    std::function<void()> onStop = NULL;

    std::vector<std::function<void(std::string)>> keyPressHandlers = {};
    std::vector<std::function<void(std::string)>> keyReleaseHandlers = {};

    std::vector<std::function<void(Vector)>> mouseLeftClickHandlers = {};
    std::vector<std::function<void(Vector)>> mouseLeftReleaseHandlers = {};

    std::vector<std::function<void(Vector)>> mouseRightClickHandlers = {};
    std::vector<std::function<void(Vector)>> mouseRightReleaseHandlers = {};

    std::vector<std::function<void(Vector)>> mouseMiddleClickHandlers = {};
    std::vector<std::function<void(Vector)>> mouseMiddleReleaseHandlers = {};

    std::vector<std::function<void(Vector)>> mouseMovementHandlers = {};

    ~Controls();

    // Delete copy constructor
    Controls(const Controls &) = delete;

    static Controls *getInstance();
    static void deleteInstance();

    void input();
    void update(float dt);
    void output(Renderer *renderer);

private:
    static Controls *instancePtr;

    Controls();

    static void invokeKeyHandlers(const std::vector<std::function<void(std::string)>> &handlers, const std::string &key);
    static void invokeMouseHandlers(const std::vector<std::function<void(Vector)>> &handlers, const Vector &mousePosition);
};
