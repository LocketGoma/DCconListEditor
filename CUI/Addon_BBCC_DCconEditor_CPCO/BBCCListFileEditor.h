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

		//FileListReader 파생
		bool ListReaderStart(std::string input);		


		virtual bool LinkingList(std::string path) override;
		bool PrintEntryList() { return BBCCListFileReader::PrintEntryList(); }	//엔트리 리스트 출력
		bool TryCompareList(); //Call Comparison
		int EditEntryFile();	//엔트리 파일 수정.
		int LoadFileList();		//파일 리스트 읽기.


		std::vector<std::string> ListReadingList();


	private :
		std::unique_ptr<FileListReader> fileListReader;
		std::vector<std::string> fileListVector;
		std::string entryPath;
		std::string tempFilePath;

		bool Comparison();				//1. 비교 수행
		bool ListEntryWriter();			//2. 조합된 리스트를 가지고 임시파일 생성.
		bool CopyCompareList();			//3. 완성된 파일을 임시파일에서 원본으로 덮어씌우기.
		
		
		std::string ConvertToUTF8(std::string input);
		std::string ConvertInputManager(std::string input);

		//std::map <std::string, int> entryList;
		//std::map <std::string, int>::iterator entryListIter;
		//std::unique_ptr<std::fstream> dcconEntry;
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