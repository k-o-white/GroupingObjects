#include <GroupingOptions.h>
#include <iostream>

double calculateDistance(const Object* obj1, const Object* obj2)
{
    double dx = obj1->getX() - obj2->getX();
    double dy = obj1->getY() - obj2->getY();
    return std::sqrt(dx * dx + dy * dy);
}

bool compareByDistance(const Object* obj1, const Object* obj2)
{
    Object zPoint(L"НулеваяКоордината", 0.0, 0.0, L"Точка", 0);
    auto distance1 = calculateDistance(obj1, &zPoint);
    auto distance2 = calculateDistance(obj2, &zPoint);
    return distance1 < distance2;
}

std::map<std::wstring, std::vector<Object*>> groupingByDistance(std::vector<Object> &objects)
{
    std::map<std::wstring, std::vector<Object*>> resultGroups;

    auto* zeroPoint = new Object(L"НулеваяКоордината", 0.0, 0.0, L"Точка", 0);

    for (auto obj : objects)
    {
        std::wstring groupName;
        double objDistance = calculateDistance(&obj, zeroPoint);
        if (objDistance < 100.0)
            groupName = L"До 100 ед.";
        else if (objDistance < 1000.0)
            groupName = L"До 1000 ед.";
        else if (objDistance < 10000.0)
            groupName = L"До 10000 ед.";
        else
            groupName = L"Слишком далеко";
        resultGroups[groupName].push_back(&obj);
    }

    for (auto group : resultGroups)
    {
        std::sort(group.second.begin(), group.second.end(), compareByDistance);
    }

    return resultGroups;
}

std::map<std::wstring, std::vector<Object*>> groupingByName(std::vector<Object> &objects)
{
    std::map<std::wstring, std::vector<Object*>> resultGroups;

    auto isCyrillic = [](char symbol)
    {
        std::string cyrillicChars = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        for (auto ch: cyrillicChars)
            if (symbol == ch)
                return true;
        return false;
    };

    for (auto obj : objects)
    {
        std::wstring name = obj.getName();
        if (!name.empty())
        {
            char firstChar = name[0];
            if (!isCyrillic(firstChar))
                firstChar = '#';
            std::wstring groupName = std::wstring(1, firstChar);
            resultGroups[groupName].push_back(&obj);
        }
    }

    for (auto group : resultGroups)
    {
        std::sort(group.second.begin(), group.second.end(), [](const Object* obj1, const Object* obj2)
        {
            return obj1->getName() < obj2->getName();
        });
    }

    return resultGroups;
}

std::map<std::wstring, std::vector<Object*>> groupingByCreationTime(std::vector<Object> &objects)
{
    std::map<std::wstring, std::vector<Object*>> resultGroups;

    for (auto obj : objects)
    {
        time_t currentTime = std::time(nullptr);
        time_t objTime = obj.getCreationTime();
        double diffDays = std::difftime(currentTime, objTime) / (60 * 60 * 24);

        std::wstring groupName;
        if (diffDays < 1)
            groupName = L"Сегодня";
        else if (diffDays < 2)
            groupName = L"Вчера";
        else if (diffDays < 7)
            groupName = L"На этой неделе";
        else if (diffDays < 30)
            groupName = L"В этом месяце";
        else if (diffDays < 365)
            groupName = L"В этом году";
        else
            groupName = L"Ранее";

        resultGroups[groupName].push_back(&obj);
    }

    for (auto group : resultGroups)
    {
        std::sort(group.second.begin(), group.second.end(), [](const Object* obj1, const Object* obj2)
        {
            return obj1->getCreationTime() < obj2->getCreationTime();
        });
    }

    return resultGroups;
}

std::map<std::wstring, std::vector<Object*>> groupingByObjectType(std::vector<Object> &objects)
{
    std::map<std::wstring, std::vector<Object*>> resultGroups;

    for (auto obj : objects)
        resultGroups[obj.getObjectType()].push_back(&obj);

    std::vector<Object*> miscellaneous;
    std::vector<std::wstring> objectTypes;
    for (const auto& group : resultGroups)
    {
        objectTypes.push_back(group.first);
    }

    for (const auto& type : objectTypes)
    {
        if (resultGroups[type].size() == 1)
        {
            auto obj = resultGroups[type][0];
            resultGroups.erase(type);
            miscellaneous.push_back(obj);
        }
    }

    if (!miscellaneous.empty())
        resultGroups[L"Разное"] = miscellaneous;

    for (auto group : resultGroups)
    {
        std::sort(group.second.begin(), group.second.end(), [](const Object* obj1, const Object* obj2)
        {
            return obj1->getName() < obj2->getName();
        });
    }

    return resultGroups;
}