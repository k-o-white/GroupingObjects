#include <GroupingOptions.h>
#include <ReadWrite.h>
#include <iostream>

double distanceFromZero(const Object* obj)
{
    double dx = obj->getX();
    double dy = obj->getY();
    return std::sqrt(std::pow(dx, 2.0) + std::pow(dy, 2.0));
}

std::map<std::wstring, std::vector<Object*>> groupingByDistance(std::vector<Object*> &objects)
{
    std::map<std::wstring, std::vector<Object*>> resultGroups;

    for (auto obj : objects)
    {
        std::string groupName;
        double objDistance = distanceFromZero(obj);
        if (objDistance < 100.0)
            groupName = "До 100 ед.";
        else if (objDistance < 1000.0)
            groupName = "До 1000 ед.";
        else if (objDistance < 10000.0)
            groupName = "До 10000 ед.";
        else
            groupName = "Слишком далеко";
        auto wGroupName = ConvertToWString(groupName);
        resultGroups[wGroupName].push_back(obj);
    }

    for (auto group : resultGroups)
    {
        std::sort(group.second.begin(), group.second.end(), [](const Object* obj1, const Object* obj2)
        {
            auto distance1 = distanceFromZero(obj1);
            auto distance2 = distanceFromZero(obj2);
            return distance1 < distance2;
        });
    }

    return resultGroups;
}

std::map<std::wstring, std::vector<Object*>> groupingByName(std::vector<Object*> &objects)
{
    std::map<std::wstring, std::vector<Object*>> resultGroups;

    auto isCyrillic = [](const wchar_t &symbol)
    {
        return symbol >= L'\u0410' && symbol <= L'\u044F';
    };

    for (auto obj : objects)
    {
        std::wstring name = obj->getName();
        if (!name.empty())
        {
            wchar_t firstChar = name[0];
            if (!isCyrillic(firstChar))
                firstChar = '#';
            auto groupName = std::wstring(1, firstChar);
            resultGroups[groupName].push_back(obj);
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

std::map<std::wstring, std::vector<Object*>> groupingByCreationTime(std::vector<Object*> &objects)
{
    std::map<std::wstring, std::vector<Object*>> resultGroups;

    for (auto obj : objects)
    {
        time_t currentTime = std::time(nullptr);
        time_t objTime = obj->getCreationTime();
        double diffDays = std::difftime(currentTime, objTime) / (60 * 60 * 24);

        std::string groupName;
        if (diffDays < 1)
            groupName = "Сегодня";
        else if (diffDays < 2)
            groupName = "Вчера";
        else if (diffDays < 7)
            groupName = "На этой неделе";
        else if (diffDays < 30)
            groupName = "В этом месяце";
        else if (diffDays < 365)
            groupName = "В этом году";
        else
            groupName = "Ранее";
        auto wGroupName = ConvertToWString(groupName);

        resultGroups[wGroupName].push_back(obj);
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

std::map<std::wstring, std::vector<Object*>> groupingByObjectType(std::vector<Object*> &objects)
{
    std::map<std::wstring, std::vector<Object*>> resultGroups;

    setlocale( LC_ALL,"Russian" );
    for (auto obj : objects)
        resultGroups[obj->getObjectType()].push_back(obj);

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
    {
        std::wstring groupName = ConvertToWString("Разное");
        resultGroups[groupName] = miscellaneous;
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