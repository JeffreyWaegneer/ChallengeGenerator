#include "FileManager.h"

#include <algorithm>

std::map <std::string, std::vector<std::string>*> FileManager::listsInMem;

std::vector<std::string>* FileManager::GetList(std::string name)
{
	std::map<std::string, std::vector<std::string>*>::iterator existsIt = FileManager::listsInMem.find(name);
	if (existsIt != FileManager::listsInMem.end())
		return (*existsIt).second;
	std::string filename = name + "s.whatever";
	std::ifstream inputFile{ filename };
	std::string buffer;
	std::vector<std::string>* res = FileManager::allocateList(name);

	if (!inputFile)
	{
		return nullptr;
	}

	while (std::getline(inputFile, buffer))
	{
		res->push_back(buffer);
	}

	inputFile.close();

	return res;
}

void FileManager::deleteList(std::string name)
{
	std::map<std::string, std::vector<std::string>*>::iterator iterToDelete = listsInMem.find(name);
	if (iterToDelete != FileManager::listsInMem.end())
	{
		delete (*iterToDelete).second;
		(*iterToDelete).second = nullptr;
		FileManager::listsInMem.erase(name);
	}
}

void FileManager::deleteAllLists()
{
	for (std::map<std::string, std::vector<std::string>*>::iterator it = FileManager::listsInMem.begin(); it != FileManager::listsInMem.end(); ++it)
	{
		delete (*it).second;
		(*it).second = nullptr;
	}
	FileManager::listsInMem.clear();
}

std::vector<std::string>* FileManager::allocateList(std::string name)
{
	std::vector<std::string>* result;

	result = new std::vector<std::string>();
	FileManager::listsInMem.insert(std::pair<std::string, std::vector<std::string>*>(name, result));

	return result;
}