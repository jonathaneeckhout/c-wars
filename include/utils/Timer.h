#pragma once

#include <functional>

class Timer
{
public:
    float timeout = 0;
    bool restart = false;

    Timer(float timeout);
    ~Timer();

    void update(float dt);

    void start();
    void stop();

    bool isRunning() { return running; };

    void setCallback(std::function<void(void *)> cb, void *data = nullptr);

private:
    bool running = false;
    float offset = 0;

    std::function<void(void *)> callback;
    void *userdata = nullptr;
};