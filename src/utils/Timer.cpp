#include <iostream>

#include "utils/Timer.h"

Timer::Timer(float timeout) : timeout(timeout) {};

Timer::~Timer() {};

void Timer::update(float dt)
{
    if (running)
    {
        offset += dt;

        if (offset >= timeout)
        {
            running = false;
            offset = 0.0f;

            std::cout << "Timer went off" << std::endl;

            if (callback)
            {
                callback(userdata);
            }
        }
    }
}

void Timer::start()
{
    running = true;
    offset = 0.0f;
}

void Timer::stop()
{
    running = false;
    offset = 0.0f;
}

void Timer::setCallback(std::function<void(void *)> cb, void *data)
{
    callback = cb;
    userdata = data;
}