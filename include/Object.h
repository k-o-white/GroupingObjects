#pragma once
#include <string>
#include <ctime>

class Object 
{
private:
    std::wstring name;
    std::wstring objectType;
    double x;
    double y;
    time_t creationTime;    
public:
    Object(std::wstring _name, double _x, double _y, std::wstring _objectType, time_t _creationTime) :
        name(std::move(_name)), x(_x), y(_y), objectType(std::move(_objectType)), creationTime(_creationTime) {};

    std::wstring getName() const;

    std::wstring getObjectType() const;

    double getX() const;

    double getY() const;

    time_t getCreationTime() const;
};