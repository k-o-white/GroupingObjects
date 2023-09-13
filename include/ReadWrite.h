//
// Created by teena on 13.09.2023.
//

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <locale>
#include <fstream>
#include <sstream>
#include <codecvt>
#include "Object.h"

std::vector<Object> readFromFile(std::string filePath);

void writeToFile(std::map<std::wstring, std::vector<Object*>> &groups);
