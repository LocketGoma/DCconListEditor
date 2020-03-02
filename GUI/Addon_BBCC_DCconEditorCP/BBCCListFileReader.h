#pragma once
#include <fstream>
#include <locale>
#include <cstdio>
#include "EngineHeader.h"

class BBCCListFileReader
{
public:
	bool LinkingList(std::string route);



private:
	std::map <std::string, bool> entryList;
	std::map <std::string, bool>::iterator entryListIter;
	std::unique_ptr<std::fstream> dcconEntry;

	bool LoadEntry(std::string);
	bool ParseEntry();
	std::string ConvertToCP949(std::string input);
	std::string ConvertToUTF8(std::string input);
	std::string ConvertInputManager(std::string input);

};

