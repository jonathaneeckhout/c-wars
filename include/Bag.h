#pragma once

#include <string>
#include <utility>

class Bag
{
public:
    float size = 100.0f;

    Bag();
    ~Bag();

    bool isFull();
    bool add(std::string type, float amount);

    std::pair<std::string, float> empty();

private:
    float stock = 0.0f;
    std::string resourceType = "Metal";
};