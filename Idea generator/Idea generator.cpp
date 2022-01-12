#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "FileManager.h"

void GenerateChallenges(std::vector<std::string>* templateList, std::vector<std::string>& result)
{
    for (unsigned int i = 0; i < templateList->size(); i++)
    {
        std::string tempString = templateList->at(i);
        int countStart = std::count(tempString.begin(), tempString.end(), '{');
        int countEnd = std::count(tempString.begin(), tempString.end(), '}');
        size_t posStart = tempString.find('{');
        size_t posEnd = tempString.find('}');

        if (posStart >= 0 && posStart < posEnd)
        {
            std::string temp = tempString.substr(posStart + 1, posEnd - posStart - 1);
            std::vector<std::string>* allTemps = FileManager::GetList(temp);

            if (allTemps == nullptr)
            {
                std::cout << temp << "s.whatever not found" << std::endl;
            }
            else
            {
                for (int i = 0; i < allTemps->size(); i++)
                {
                    std::string buffer = tempString.replace(posStart, posEnd - posStart + 1, allTemps->at(i));
                    result.push_back(buffer);
                }

                FileManager::deleteList(temp);
            }
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