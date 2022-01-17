#include "ChallengeGenerator.h"
#include <iostream>
#include "FileManager.h"

void ChallengeGenerator::Init()
{
    for (unsigned int i = 0; i < 9; i++)
    {
        std::string listName = ChallengeGenerator::GetTextForEnum(DIFFICULTY(i)) + "Challenge";
        std::cout << "Getting " << listName << " list from file" << std::endl;
        FileManager::GetList(listName);
    }
}

void ChallengeGenerator::CleanUp()
{
    FileManager::deleteAllLists();
}

std::string ChallengeGenerator::GenerateChallenge(DIFFICULTY diff)
{
    srand(time(0));
    std::string listName = ChallengeGenerator::GetTextForEnum(diff) + "Challenge";
    std::vector<std::string>* templateList = FileManager::GetList(listName);
    std::string tempString = templateList->at(rand() % templateList->size());
    ChallengeGenerator::LoadAllListsForTemplate(tempString);
    int countStart = std::count(tempString.begin(), tempString.end(), '{');
    int countEnd = std::count(tempString.begin(), tempString.end(), '}');
    if (countStart != countEnd)
        return "Invalid symbol number";

    for (unsigned int i = 0; i < countStart; i++)
    {
        int posStart = tempString.find('{');
        int posEnd = tempString.find('}');
        std::string temp = tempString.substr(posStart + 1, posEnd - posStart - 1);
        std::vector<std::string>* l = FileManager::GetList(temp);
        tempString.replace(posStart, posEnd - posStart + 1, l->at(rand() % l->size()));
    }

    return tempString;
}

std::string ChallengeGenerator::GetTextForEnum(DIFFICULTY d)
{
    const std::string EnumStrings[9] = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Diamond", "Master", "Grandmaster", "Challenger" };
    return EnumStrings[(int)d];
}

void ChallengeGenerator::LoadAllListsForTemplate(std::string challengeTemplate)
{
    int countStart = std::count(challengeTemplate.begin(), challengeTemplate.end(), '{');
    int countEnd = std::count(challengeTemplate.begin(), challengeTemplate.end(), '}');
    size_t posStart = challengeTemplate.find('{');
    size_t posEnd = challengeTemplate.find('}');
    if (countStart != countEnd)
    {
        std::cout << "{} aren't valid" << std::endl;
        return;
    }

    while (posStart >= 0 && posStart < posEnd)
    {
        std::string tempName = challengeTemplate.substr(posStart + 1, posEnd - posStart - 1);
        FileManager::GetList(tempName);
        posStart = tempName.find('{', posEnd);
        posEnd = tempName.find('}', posEnd);
    }
}

//std::queue<std::string>* ReplaceTemplateRecursive(std::string temp)
//{
//    std::queue<std::string>* result;
//    int posStart = temp.find('{');
//    int posEnd = temp.find('}');
//    std::string templateName = temp.substr(posStart + 1, posEnd - posStart - 1);
//
//    if (posStart < 0 && posEnd < 0)
//    {
//        result = new std::queue<std::string>();
//        result->push(temp);
//        return result;
//    }
//
//    std::string next = temp.replace(posStart, posEnd - posStart + 1, "");
//
//    result = ReplaceTemplateRecursive(next);
//    std::vector<std::string>* possibleTempNames = FileManager::GetList(templateName);
//    const int size = result->size();
//
//    for (int i = 0; i < size; i++)
//    {
//        std::string buffer = result->front();
//        result->pop();
//        for (std::vector<std::string>::iterator j = possibleTempNames->begin(); j != possibleTempNames->end(); j++)
//        {
//            std::string t = buffer;
//            t.insert(posStart, *j);
//            result->push(t);
//        }
//    }
//
//    return result;
//}
