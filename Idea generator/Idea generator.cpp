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

std::string GenerateRandomChallenge(std::vector<std::string>* templateList)
{
    srand(time(0));
    std::string tempString = templateList->at(rand() % templateList->size());
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

int main(int argc, char** argv)
{
    srand(time(0));
    std::vector<std::string>* challengeTemplates = FileManager::GetList("challenge");
    std::string argv1(argv[1]);
    
    if (challengeTemplates == nullptr)
    {
        std::cout << "challenges.whatever not found" << std::endl;
        return 0;
    }

    if (argv1 == "/list")
    {
        std::string fileName;
        if (argv[2] == nullptr)
            fileName = "GeneratedChallenges.whatever";
        else
            fileName = argv[2];

        std::vector<std::string> allPossibleChallenges;

        GenerateChallenges(challengeTemplates, allPossibleChallenges);
        std::random_shuffle(allPossibleChallenges.begin(), allPossibleChallenges.end());

        FileManager::WriteList(fileName, &allPossibleChallenges);

        std::cout << "Generated challenges can be found in the '" << fileName << "' file" << std::endl;
    }

    if (argv1 == "/challenge")
    {
        std::string challenge = GenerateRandomChallenge(challengeTemplates);
        std::cout << challenge << std::endl;
    }
    
    FileManager::deleteAllLists();

    return 0;
}