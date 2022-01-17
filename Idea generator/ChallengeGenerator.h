#pragma once
#include<string>
#include<vector>

enum class DIFFICULTY
{
	IRON = 0,
	BRONZE = 1,
	SILVER = 2,
	GOLD = 3,
	PLATINUM = 4,
	DIAMOND = 5,
	MASTER = 6,
	GRANDMASTER = 7,
	CHALLENGER = 8
};

class ChallengeGenerator
{
public:
	/// <summary>
	/// This function initializes all the lists from the files;
	/// </summary>
	static void Init();
	static void CleanUp();
	/// <summary>
	/// This function generates one random challenge.;
	/// </summary>
	/// <param name="diff">Difficulty for the challenge. See DIFFICULTY enum</param>
	/// <returns>The challenge in a string</returns>
	static std::string GenerateChallenge(DIFFICULTY diff);
	
private:
	static std::string GetTextForEnum(DIFFICULTY d);
	static void LoadAllListsForTemplate(std::string challengeTemplate);
};
