
#pragma once

#include "core/Renderer.hpp"
#include "utils/Vector.hpp"
#include "collision/CollisionShapeSquare.hpp"

class WorkerMenu
{
public:
    bool visible = true;

    WorkerMenu();
    ~WorkerMenu();

    void input();
    void update(float dt);
    void output(Renderer *renderer);

    bool isMouseAbove(Vector mousePosition);

private:
    const Vector size = {200, 200};

    const Vector position = {Renderer::windowSize.x - size.x, Renderer::windowSize.y - size.y};

    CollisionShapeSquare square = CollisionShapeSquare(position, size);
};