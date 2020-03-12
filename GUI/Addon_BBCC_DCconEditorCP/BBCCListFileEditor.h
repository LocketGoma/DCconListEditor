#pragma once
#include "FileListReader.h"
#include "BBCCListFileReader.h"
#include "EngineHeader.h"


/*
	�۵����� :
		1. LinkingList���� ListEntry�� �д´�. (LoadEntry())
		2. LoadEntry()���� ���� �����͸� Parsing �Ѵ�. (ParseEntry())
		2-2. ParseEntry() ���� ConvertToCP949() �޼ҵ� ȣ��� wstring -> string���� ��ȯ.
		3. Comparison() ���� (���� ����Ʈ�� ����Ʈ���ϵ����͸� ��)
		4. FileEdit() ����
		4-2. ConvertToUTF8() ȣ��, string -> wstring���� ��ȯ
		4-3. ConvertInputManager() ���� ��Ŀ� �°� ���� ���
		5. ���� �ϼ�.

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