// TestApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "FileManager.h"
#include "ChallengeGenerator.h"
int main()
{
    ChallengeGenerator::Init();
    std::string c = ChallengeGenerator::GenerateChallenge(DIFFICULTY::BRONZE);
    std::cout << c << std::endl;
}