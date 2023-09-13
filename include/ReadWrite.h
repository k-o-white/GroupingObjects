//
// Created by teena on 13.09.2023.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <locale>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <windows.h>
#include <filesystem>
#include <exception>
#include "Object.h"

class FailedToOpenFileException : public std::exception
{
public:
    FailedToOpenFileException() = default;

    [[nodiscard]] const char* what() const noexcept override;
};

std::wstring ConvertToWString(const std::string &source);

std::stringstream ReadFromFile(std::string path);

std::vector<Object> getObjectList(std::string filePath);

void writeToFile(std::map<std::wstring, std::vector<Object*>> &groups);

