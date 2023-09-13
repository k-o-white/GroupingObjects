//
// Created by teena on 13.09.2023.
//

#include "ReadWrite.h"

const char* FailedToOpenFileException::what() const noexcept
{
    return "Failed to open file: ";
}

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

std::stringstream ReadFromFile(const std::string& path)
{
    std::ifstream f(path);
    if (!f.is_open())
    {
        throw FailedToOpenFileException();
    }
    std::stringstream ss;
    ss << f.rdbuf();
    return ss;
}

std::vector<Object*> getObjectList(const std::string& filePath)
{
    std::vector<Object*> objs;
    std::stringstream fileContent;
    fileContent = ReadFromFile(filePath);
    std::string line;
    while (std::getline(fileContent, line))
    {
        std::wstring wLine = ConvertToWString(line);
        std::wistringstream iss(wLine);
        std::wstring name, objectType;
        double x, y;
        time_t creationTime;
        iss >> name >> x >> y >> objectType >> creationTime;
        auto obj = new Object(name, x, y, objectType, creationTime);
        objs.push_back(obj);
    }
    return objs;
}

void writeToFile(std::map<std::wstring, std::vector<Object*>> &groups, std::string &fileName)
{
    std::wofstream outFile("..\\resources\\" + fileName + ".txt");

    if (!outFile.is_open())
    {
        throw FailedToOpenFileException();
    }

    outFile.imbue(std::locale(outFile.getloc(), new std::codecvt_utf8<wchar_t, 0x10FFFF, std::consume_header>));

    auto space = ConvertToWString(" ");
    auto newline = ConvertToWString("\n");
    auto groupWord = ConvertToWString("Группа: ");

    for (auto& group : groups)
    {
        outFile << groupWord << group.first << newline;
        for (auto* obj : group.second)
        {
            outFile << obj->getName() << space;
            outFile << obj->getX() << space;
            outFile << obj->getY() << space;
            outFile << obj->getObjectType() << space;
            outFile << obj->getCreationTime() << newline;
        }
        outFile << newline;
    }
    outFile.close();
}