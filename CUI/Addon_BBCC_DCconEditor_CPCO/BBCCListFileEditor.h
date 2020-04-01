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

		//FileListReader �Ļ�
		bool ListReaderStart(std::string input);		


		virtual bool LinkingList(std::string path) override;
		bool PrintEntryList() { return BBCCListFileReader::PrintEntryList(); }	//��Ʈ�� ����Ʈ ���
		bool TryCompareList(); //Call Comparison
		int EditEntryFile();	//��Ʈ�� ���� ����.
		int LoadFileList();		//���� ����Ʈ �б�.


		std::vector<std::string> ListReadingList();


	private :
		std::unique_ptr<FileListReader> fileListReader;
		std::vector<std::string> fileListVector;
		std::string entryPath;
		std::string tempFilePath;

		bool Comparison();				//1. �� ����
		bool ListEntryWriter();			//2. ���յ� ����Ʈ�� ������ �ӽ����� ����.
		bool CopyCompareList();			//3. �ϼ��� ������ �ӽ����Ͽ��� �������� ������.
		
		
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