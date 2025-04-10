#pragma once

class CollisionShape
{
public:
    virtual bool collidesWith(const CollisionShape &other) const = 0;
};