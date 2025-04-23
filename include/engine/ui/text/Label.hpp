#pragma once

#include "engine/ui/text/Text.hpp"

class Label : public Text
{
public:
    Label(Vector position, const std::string &text);
    ~Label();

private:
    void output() override;
};