#include <iostream>
#include <vector>
#include "GroupingOptions.h"
#include "ReadWrite.h"

enum option {DISTANCE = 1, NAME, CREATION_TIME, OBJECT_TYPE};

int main() 
{
    std::vector<Object> objects;
    std::string path = "..\\resources\\data3.txt";
    try
    {
        objects = getObjectList(path);
    }
    catch (const FailedToOpenFileException &fail)
    {
        std::cerr << fail.what() << path << std::endl;
        return 1;
    }
    std::map<std::wstring, std::vector<Object*>> result;
    int option;
    std::cout << "Choose option to group objects: ";
    std::cin >> option;

    switch (option)
    {
        case DISTANCE:
            result = groupingByDistance(objects);
            break;
        case NAME:
            result = groupingByName(objects);
            break;
        case CREATION_TIME:
            result = groupingByCreationTime(objects);
            break;
        case OBJECT_TYPE:
            result = groupingByObjectType(objects);
            break;
        default:
            std::cout << "Input is invalid." << std::endl;
    }

    writeToFile(result);

    for (const auto& group : result)
    {
        for (auto obj : group.second)
        {
            delete obj;
            obj = nullptr;
        }
    }
    return 0;
}

