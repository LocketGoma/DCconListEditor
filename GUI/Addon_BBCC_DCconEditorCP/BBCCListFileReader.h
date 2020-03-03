#pragma once
#include "EngineHeader.h"
#include <fstream>
#include <locale>
#include <cstdio>
#include "addition/include/iconv.h"


class BBCCListFileReader
{
public:	
	bool LinkingList(std::string route);



private:
	iconv_t changer;

	std::map <std::string, bool> entryList;
	std::map <std::string, bool>::iterator entryListIter;
	std::unique_ptr<std::fstream> dcconEntry;

	bool ChangeReady();
	bool ChangeEnd();

	bool LoadEntry(std::string);
	bool ParseEntry();
	std::string ConvertToCP949(std::string input);


};

