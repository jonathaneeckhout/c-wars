#include "engine/Object.hpp"
#include "engine/utils/uuid.hpp"

Object::Object()
{
    id = generate_uuid();
};

Object::~Object()
{
    for (auto &pair : children)
    {
        delete pair.second;
    }
}

const std::string &Object::getId() const
{
    return id;
}

Object *Object::getParent() const
{
    return parent;
}

std::map<std::string, Object *> &Object::getChildren()
{
    return children;
}

Object *Object::getChild(const std::string &id)
{
    if (children.find(id) == children.end())
    {
        return nullptr;
    }

    return children[id];
}

Object *Object::getChildByName(const std::string &name)
{
    for (auto &pair : children)
    {
        if (pair.second->name == name)
        {
            return pair.second;
        }
    }

    return nullptr;
}

bool Object::addChild(Object *object)
{
    if (getChild(object->getId()) != nullptr)
    {
        return false;
    }

    children[object->getId()] = object;

    return true;
}

bool Object::removeChild(const std::string &id)
{
    if (getChild(id) == nullptr)
    {
        return false;
    }

    children.erase(id);

    return true;
}

bool Object::deleteChild(const std::string &id)
{
    if (getChild(id) == nullptr)
    {
        return false;
    }

    delete children[id];

    return removeChild(id);
}

void Object::__input()
{
    for (auto &pair : children)
    {
        pair.second->__input();
    }

    input();
}

void Object::__update(float dt)
{
    for (auto &pair : children)
    {
        pair.second->__update(dt);
    }

    update(dt);
}

void Object::__output()
{
    for (auto &pair : children)
    {
        pair.second->__output();
    }

    output();
}

void Object::input() {}

void Object::update(float) {}

void Object::output() {}
