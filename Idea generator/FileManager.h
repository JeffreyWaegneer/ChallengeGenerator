#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <list>
#include <map>

class FileManager
{
public:
	static std::vector<std::string>* GetList(std::string name);
	static void WriteList(std::string fileName, std::vector<std::string>* listToWrite);

	static void deleteList(std::string name);
	static void deleteAllLists();

private:
	static std::map<std::string, std::vector<std::string>*> listsInMem;
	static std::vector<std::string>* allocateList(std::string name);
};