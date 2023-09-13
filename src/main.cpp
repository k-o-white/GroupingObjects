#include <iostream>
#include <vector>
#include "GroupingOptions.h"
#include "ReadWrite.h"

enum option {DISTANCE = 1, NAME, CREATION_TIME, OBJECT_TYPE};

int main() 
{
    auto objects = readFromFile("..\\resources\\data.txt");
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

