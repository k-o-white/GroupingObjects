#pragma once
#include <Object.h>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

std::map<std::wstring, std::vector<Object*>> groupingByDistance(std::vector<Object*> &objects);

std::map<std::wstring, std::vector<Object*>> groupingByName(std::vector<Object*> &objects);

std::map<std::wstring, std::vector<Object*>> groupingByCreationTime(std::vector<Object*> &objects);

std::map<std::wstring, std::vector<Object*>> groupingByObjectType(std::vector<Object*> &objects);