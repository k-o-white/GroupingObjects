//
// Created by teena on 13.09.2023.
//

#include "ReadWrite.h"

std::wstring ConvertToWString(const std::string &source)
{
    std::wstring wstr;
    if (auto sizeAfterConversion = MultiByteToWideChar(CP_UTF8, 0, source.data(), source.size(), nullptr, 0))
    {
        wstr.resize(sizeAfterConversion);
    }
    if (!MultiByteToWideChar(CP_UTF8, 0, source.data(), source.size(), &wstr[0], wstr.size()))
    {
        return {};
    }
    return wstr;
}

std::stringstream ReadFromFile(std::string path)
{
    std::ifstream f(path);
    if (!f.is_open())
    {
        exit(1);
    }
    std::stringstream ss;
    ss << f.rdbuf();
    return ss;
}

std::vector<Object> getObjectList(std::string filePath)
{
    std::vector<Object> objs;
    auto fileContent = ReadFromFile("..\\resources\\data.txt");
    std::string line;
    while (std::getline(fileContent, line))
    {
        std::wstring wLine = ConvertToWString(line);
        std::wistringstream iss(wLine);
        std::wstring name, objectType;
        double x, y;
        time_t creationTime;
        iss >> name >> x >> y >> objectType >> creationTime;
        auto obj = Object(name, x, y, objectType, creationTime);
        objs.push_back(obj);
    }
    return objs;
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