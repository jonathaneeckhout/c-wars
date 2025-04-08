#pragma once
#include <math.h>

class Vector
{
public:
    float x = 0.0f, y = 0.0f;

    Vector(float x, float y) : x(x), y(y) {}
    Vector() : x(0), y(0) {}

    Vector operator+(const Vector &other) const
    {
        return Vector(this->x + other.x, this->y + other.y);
    }

    Vector operator-(const Vector &other) const
    {
        return Vector(this->x - other.x, this->y - other.y);
    }

    Vector operator*(const Vector &other) const
    {
        return Vector(this->x * other.x, this->y * other.y);
    }

    Vector operator/(const Vector &other) const
    {
        return Vector(this->x / other.x, this->y / other.y);
    }

    Vector operator*(const float &other) const
    {
        return Vector(this->x * other, this->y * other);
    }

    Vector operator/(const float &other) const
    {
        return Vector(this->x / other, this->y / other);
    }

    bool operator==(const Vector &other) const
    {
        return this->x == other.x && this->y == other.y;
    }

    bool operator!=(const Vector &other) const
    {
        return this->x != other.x || this->y != other.y;
    }

    Vector &operator+=(const Vector &other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vector &operator-=(const Vector &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    Vector &operator*=(const Vector &other)
    {
        this->x *= other.x;
        this->y *= other.y;
        return *this;
    }

    Vector &operator/=(const Vector &other)
    {
        this->x /= other.x;
        this->y /= other.y;
        return *this;
    }

    Vector &operator*=(const float &other)
    {
        this->x *= other;
        this->y *= other;
        return *this;
    }

    Vector &operator/=(const float &other)
    {
        this->x /= other;
        this->y /= other;
        return *this;
    }

    float magnitude() const
    {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    Vector normalize() const
    {
        float magnitude = this->magnitude();

        if (magnitude == 0)
        {
            return Vector(0, 0);
        }

        return Vector(this->x / magnitude, this->y / magnitude);
    }
};