#include "Group.h"
#include <algorithm>

#include "entities/Unit.h"

Group::Group(std::string owner) : owner(owner) {}

Group::~Group() {}

bool Group::addMember(const std::string &member)
{
    if (std::find(members.begin(), members.end(), member) != members.end())
        return false; // already in group

    members.push_back(member);
    return true;
}

bool Group::removeMember(const std::string &member)
{
    auto it = std::remove(members.begin(), members.end(), member);
    if (it != members.end())
    {
        members.erase(it, members.end());
        return true;
    }
    return false;
}

void Group::clear()
{
    members.clear();
}

const std::vector<std::string> &Group::getMembers() const
{
    return members;
}

void Group::move(Vector position)
{
    for (auto member : members)
    {
        Entity *entity = map->getEntity(member);
        if (entity == NULL)
        {
            continue;
        }

        Unit *unit = dynamic_cast<Unit *>(entity);
        if (unit == NULL)
        {
            continue;
        }

        if (unit->player != owner)
        {
            continue;
        }

        unit->move(position);
    }
}