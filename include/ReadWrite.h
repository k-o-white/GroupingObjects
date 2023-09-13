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
#include "Object.h"
#include <windows.h>
#include <filesystem>

std::wstring ConvertToWString(const std::string &source);

std::stringstream ReadFromFile(std::string path);

std::vector<Object> getObjectList(std::string filePath);

void writeToFile(std::map<std::wstring, std::vector<Object*>> &groups);
