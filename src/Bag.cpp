#include <algorithm>

#include "Bag.h"

Bag::Bag() {};

Bag::~Bag() {};

bool Bag::isFull()
{
    return stock >= size;
}

bool Bag::add(std::string type, float amount)
{
    if (isFull())
    {
        return false;
    }

    if (resourceType == type)
    {
        stock += amount;
    }
    else
    {
        resourceType = type;
        stock = amount;
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