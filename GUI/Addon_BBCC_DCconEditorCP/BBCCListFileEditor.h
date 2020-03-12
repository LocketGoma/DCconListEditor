#pragma once
#include "FileListReader.h"
#include "BBCCListFileReader.h"
#include "EngineHeader.h"


/*
	작동구조 :
		1. LinkingList에서 ListEntry를 읽는다. (LoadEntry())
		2. LoadEntry()에서 읽은 데이터를 Parsing 한다. (ParseEntry())
		2-2. ParseEntry() 에서 ConvertToCP949() 메소드 호출로 wstring -> string으로 변환.
		3. Comparison() 수행 (파일 리스트와 리스트파일데이터를 비교)
		4. FileEdit() 수행
		4-2. ConvertToUTF8() 호출, string -> wstring으로 변환
		4-3. ConvertInputManager() 에서 양식에 맞게 파일 출력
		5. 파일 완성.

*/
class BBCCListFileEditor : BBCCListFileReader
{
	public :		
		BBCCListFileEditor();
		virtual bool LinkingList(std::string route) override;
		bool TryCompareList(); //Call Comparison

	private :
		bool Comparison();

		std::unique_ptr<FileListReader> fileListReader;
		void ListEntryWriter();
		
		std::vector<std::string> fileListVector;
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