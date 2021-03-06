#pragma once
#include "EngineHeader.h"
#include <fstream>
#include <locale>
#include <cstdio>
#include <vector>
#include "addition/include/iconv.h"



class BBCCListFileReader
{
public:		
	virtual bool LinkingList(std::string route);
	bool PrintEntryList();
	bool Clear();

private:	
	std::unordered_map <std::string, std::vector<std::string>> entryList;
	std::unordered_map <std::string, std::vector<std::string>>::iterator entryListIter;
	std::unique_ptr<std::fstream> dcconEntry;

	bool LoadEntry(std::string);
	bool ParseEntry();
	std::string ConvertToCP949(std::string input);

	friend class BBCCListFileEditor;
};

