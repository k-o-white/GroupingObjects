#include <iostream>
#include <vector>
#include "GroupingOptions.h"
#include "ReadWrite.h"

enum option {DISTANCE = 1, NAME, CREATION_TIME, OBJECT_TYPE};

void printOptions()
{
    std::cout << "Here's options for grouping objects:" << std::endl;
    std::cout << "1 - by distance;" << std::endl;
    std::cout << "2 - by name;" << std::endl;
    std::cout << "3 - by creation time;" << std::endl;
    std::cout << "4 - by object type." << std::endl;
}

int main() 
{
    std::vector<Object*> objects;
    std::string path = "..\\resources\\data.txt";
    try
    {
        objects = getObjectList(path);
    }
    catch (const FailedToOpenFileException &fail)
    {
        std::cerr << fail.what() << path << std::endl;
        return 1;
    }

    std::cout << "Data is loaded from file \"data.txt\"" << std::endl;
    std::map<std::wstring, std::vector<Object*>> result;

    printOptions();
    unsigned int option;
    std::cout << "Choose option: ";
    std::cin >> option;

    while (option < DISTANCE || option > OBJECT_TYPE)
    {
        std::cout << "Try again. ";
        std::cout << "Choose option: ";
        std::cin >> option;
    }

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
            return 1;
    }

    std::string fileName;
    std::cout << "Input file name without extension: ";
    std::cin >> fileName;

    try
    {
        writeToFile(result, fileName);
    }
    catch (const FailedToOpenFileException &fail)
    {
        std::cerr << fail.what() << fileName << ".txt" << std::endl;
        return 1;
    }

    std::cout << "Data successfully written to resources/" << fileName << ".txt" << std::endl;

    for (auto obj : objects)
    {
        delete obj;
        obj = nullptr;
    }
    return 0;
}

