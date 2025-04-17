#include "player/PlayerResources.hpp"

PlayerResources::PlayerResources() {}

PlayerResources::~PlayerResources() {}

bool PlayerResources::add(std::pair<std::string, float> resource)
{
    if (resource.first == "Metal")
    {
        metal += resource.second;
        return true;
    }

    return false;
}

bool PlayerResources::remove(std::map<std::string, float> resources)
{
    for (const auto &resource : resources)
    {
        if (resource.first == "Metal" && resource.second > metal)
        {
            return false;
        }
    }

    for (const auto &resource : resources)
    {
        if (resource.first == "Metal")
        {
            metal -= resource.second;
        }
    }

    return true;
}

std::map<std::string, float> PlayerResources::get() const
{
    return {{"Metal", metal}};
}