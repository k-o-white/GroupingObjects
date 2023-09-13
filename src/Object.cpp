#include <Object.h>

std::wstring Object::getName() const
{
    return this->name;
}

std::wstring Object::getObjectType() const
{
    return this->objectType;
}

double Object::getX() const
{
    return this->x;
}

double Object::getY() const
{
    return this->y;
}

time_t Object::getCreationTime() const
{
    return this->creationTime;
}