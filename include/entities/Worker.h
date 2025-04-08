#pragma once

#include "Entity.h"

class Worker : public Entity
{
public:
    Worker(Vector position);
    ~Worker();
    void update(float dt) override;
    void output(SDL_Renderer *renderer,  Camera *camera) override;
};