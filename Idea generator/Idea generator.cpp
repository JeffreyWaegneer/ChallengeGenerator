#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <queue>
#include "FileManager.h"

void LoadAllListsForTemplate(std::string temp)
{
    int countStart = std::count(temp.begin(), temp.end(), '{');
    int countEnd = std::count(temp.begin(), temp.end(), '}');
    size_t posStart = temp.find('{');
    size_t posEnd = temp.find('}');
    if (countStart != countEnd)
    {
        std::cout << "{} aren't valid" << std::endl;
        return;
    }

    while (posStart >= 0 && posStart < posEnd)
    {
        std::string tempName = temp.substr(posStart + 1, posEnd - posStart - 1);
        FileManager::GetList(tempName);
        posStart = tempName.find('{', posEnd);
        posEnd = tempName.find('}', posEnd);
    }
}

std::queue<std::string>* ReplaceTemplateRecursive(std::string temp)
{
    std::queue<std::string>* result;
    int posStart = temp.find('{');
    int posEnd = temp.find('}');
    std::string templateName = temp.substr(posStart + 1, posEnd - posStart - 1);

    if (posStart < 0 && posEnd < 0)
    {
        result = new std::queue<std::string>();
        result->push(temp);
        return result;
    }
   
    std::string next = temp.replace(posStart, posEnd - posStart + 1, "");

    result = ReplaceTemplateRecursive(next);
    std::vector<std::string>* possibleTempNames = FileManager::GetList(templateName);
    const int size = result->size();

    for (int i = 0; i < size; i++)
    {
        std::string buffer = result->front();
        result->pop();
        for (std::vector<std::string>::iterator j = possibleTempNames->begin(); j != possibleTempNames->end(); j++)
        {
            std::string t = buffer;
            t.insert(posStart, *j);
            result->push(t);
        }
    }

    return result;
}

void GenerateChallenges(std::vector<std::string>* templateList, std::vector<std::string>& result)
{
    for (unsigned int i = 0; i < templateList->size(); i++)
    {
        std::string tempString = templateList->at(i);
        size_t posStart = tempString.find('{');
        size_t posEnd = tempString.find('}');

        LoadAllListsForTemplate(tempString);

        std::queue<std::string>* temp = ReplaceTemplateRecursive(tempString);

        const unsigned int size = temp->size();
        for (unsigned int i = 0; i < size; i++)
        {
            result.push_back(temp->front());
            temp->pop();
        }
    }
}

int main()
{
    srand(time(0));

    std::vector<std::string>* challengeTemplates = FileManager::GetList("challenge");
    std::vector<std::string> allPossibleChallenges;

    if (challengeTemplates == nullptr)
    {
        std::cout << "challenges.whatever not found" << std::endl;
        return 0;
    }
    
    GenerateChallenges(challengeTemplates, allPossibleChallenges);
    std::random_shuffle(allPossibleChallenges.begin(), allPossibleChallenges.end());

    for (std::vector<std::string>::iterator i = allPossibleChallenges.begin(); i != allPossibleChallenges.end(); i++)
    {
        std::cout << *i << std::endl;
    }

    FileManager::deleteAllLists();

    return 0;
}