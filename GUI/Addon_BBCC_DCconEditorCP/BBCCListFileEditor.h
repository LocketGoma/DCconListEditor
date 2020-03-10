#pragma once
#include "FileListReader.h"
#include "BBCCListFileReader.h"
#include "EngineHeader.h"

//둘다 상속!
class BBCCListFileEditor : BBCCListFileReader
{
	public :
		virtual bool LinkingList(std::string route);



	private :
		std::unique_ptr<FileListReader> fileListReader;		

		std::string ConvertToUTF8(std::string input);
		std::string ConvertInputManager(std::string input);
};


/*
class FileListReader
{
public:
	void ListReaderEngineStarter(std::string input);
	std::vector<std::string> ListPrinter();

private:
	const std::string valid_ext_list[3] = { ".jpg",".gif",".png" };
	std::map <std::string, bool> fileList;
	std::map <std::string, bool>::iterator fileListIter;

	bool FileListReadingEngine(std::string path);

};
*/
/*
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


*/