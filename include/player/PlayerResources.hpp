#pragma once

#include <string>
#include <utility>
#include <map>

class PlayerResources
{
public:
    float metal = 0.0f;

    PlayerResources();
    ~PlayerResources();

    bool add(std::pair<std::string, float> resource);

    bool remove(std::map<std::string, float> resources);

    std::map<std::string, float> get() const;
};