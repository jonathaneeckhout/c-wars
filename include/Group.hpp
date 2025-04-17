#pragma once
#include <vector>
#include <string>
#include <functional>

#include "utils/Vector.hpp"
#include "maps/Map.hpp"
#include "entities/units/Unit.hpp"

class Group
{
public:
    std::string owner = "";
    Map *map = NULL;

    Group(std::string owner);
    ~Group();

    bool addMember(const std::string &member);
    bool removeMember(const std::string &member);
    void clear();

    const std::vector<std::string> &getMembers() const;

    void move(Vector position);
    void interact(Entity *entity);

private:
    std::vector<std::string> members;
    void forEachOwnedUnit(std::function<void(Unit *)> action);
};
