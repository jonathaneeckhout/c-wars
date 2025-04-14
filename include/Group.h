#pragma once
#include <vector>
#include <string>

#include "utils/Vector.h"
#include "maps/Map.h"

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

private:
    std::vector<std::string> members;
};
