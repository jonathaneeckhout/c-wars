#pragma once
#include <vector>
#include <string>

class Group
{
public:
    Group();
    ~Group();

    bool addMember(const std::string &member);
    bool removeMember(const std::string &member);
    void clear();

    const std::vector<std::string> &getMembers() const;

private:
    std::vector<std::string> members;
};
