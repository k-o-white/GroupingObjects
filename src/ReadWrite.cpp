//
// Created by teena on 13.09.2023.
//

#include "ReadWrite.h"

std::vector<Object> readFromFile(std::string filePath)
{
    std::vector<Object> objs;
    std::wifstream readFile("../resources/data.txt");
    readFile.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    std::wstringstream wss;
    wss << readFile.rdbuf();

    std::wstring line;
    while (std::getline(wss, line))
    {
        std::wistringstream iss(line);
        std::wstring name, objectType;
        double x, y;
        time_t creationTime;
        iss >> name >> x >> y >> objectType >> creationTime;
        auto obj = Object(name, x, y, objectType, creationTime);
        objs.push_back(obj);
    }
    readFile.close();
}

void writeToFile(std::map<std::wstring, std::vector<Object*>> &groups)
{
    std::string fileName;
    std::cout << "Input file name: ";
    std::cin >> fileName;
    std::wofstream outFile("..\\resources\\" + fileName + ".txt");

    if (!outFile.is_open())
    {
        std::cerr << "Unable to open the file: " << fileName << ".txt" << std::endl;
        return;
    }

    for (auto& group : groups)
    {
        outFile << L"Группа: " << group.first << L"\n";
        for (auto* obj : group.second)
        {
            outFile << obj->getName() << L" ";
            outFile << obj->getX() << L" ";
            outFile << obj->getY() << L" ";
            outFile << obj->getObjectType() << L" ";
            outFile << obj->getCreationTime() << L"\n";
        }
        outFile << L"\n";
    }
    outFile.close();
}