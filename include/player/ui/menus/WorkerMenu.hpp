
#pragma once

#include "core/Renderer.hpp"
#include "utils/Vector.hpp"

class WorkerMenu
{
public:
    bool visible = false;

    WorkerMenu();
    ~WorkerMenu();

    void input();
    void update(float dt);
    void output(Renderer *renderer);

private:
    const Vector size = {200, 200};

    const Vector position = {Renderer::windowSize.x - size.x, Renderer::windowSize.y - size.y};
};