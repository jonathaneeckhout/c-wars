#include <algorithm>

#include "Bag.hpp"

Bag::Bag() {};

Bag::~Bag() {};

bool Bag::isFull()
{
    return stock >= size;
}

bool Bag::add(std::pair<std::string, float> stuff)
{
    if (isFull())
    {
        return false;
    }

    if (resourceType == stuff.first)
    {
        stock += stuff.second;
    }
    else
    {
        resourceType = stuff.first;
        stock = stuff.second;
    }

    // clamp the stock to the bag's size
    stock = std::min(stock, size);

    return true;
}

std::pair<std::string, float> Bag::empty()
{
    std::pair<std::string, float> result = {resourceType, stock};

    stock = 0.0f;
    resourceType = "";

    return result;
}