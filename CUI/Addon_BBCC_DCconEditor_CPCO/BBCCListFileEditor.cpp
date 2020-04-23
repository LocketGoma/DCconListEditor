#include "BBCCListFileEditor.h"

BBCCListFileEditor::BBCCListFileEditor() {
	fileListReader = std::make_unique<FileListReader>();	
	tempFilePath = "temp.bat";
}


bool BBCCListFileEditor::TryCompareList() {
	return Comparison();
}


bool BBCCListFileEditor::LinkingList(std::string path) {	
	if (path.empty() == true) {
		entryPath = "lib/dccon_list.js";
	}
	else {
		entryPath = path;
	}
	if (LoadEntry(entryPath) == false) {
		std::cout << "��Ʈ�� ������ ��γ� ������ �߸��Ǿ����ϴ�." << std::endl;
		return false;
	}
	if (ParseEntry() == false) {
		std::cout << "��Ʈ�� ������ ������ �Ϻΰ� �߸��Ǿ����ϴ�." << std::endl;
		return false;
	}
	return true;
}

//���Ⱑ �����Ŀ����������ϴ���
bool BBCCListFileEditor::Comparison() {	
	//����Ʈ ��Ʈ��
	int listEntrySize = entryList.size();
	//���� ����Ʈ
	int FileListSize = fileListVector.size();	
	try {
		for (entryListIter = entryList.begin() ; entryListIter != entryList.end() ; ++entryListIter){
			for (int i = 0; i < FileListSize; i++) {
				if (fileListVector[i].compare(entryListIter->first) == 0) {
					entryListIter->second++;
				}
			}
		}
	}
	catch (std::exception e) {
		return false;
	}
	return true;
}

int BBCCListFileEditor::EditEntryFile() {	
	//0		: ����
	//1		: ���� ����Ʈ�� �������
	//2		: ����Ʈ �񱳽� �̻�
	//3		: �ӽ� ���� ������ �̻�
	//4		: �ӽ� ���� ����� �̻�
	//-1	: �� �� ����
	try {
		if (fileListVector.empty() == true) {
			return 1;
		}
		if (TryCompareList() == false) {
			return 2;
		}
		if (ListEntryWriter() == false) {
			return 3;
		}
		if (CopyCompareList() == false) {
			return 4;
		}
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}

//���� �߿��ϰ� �����ؾ��ϴ� �κ�
bool BBCCListFileEditor::ListEntryWriter() {
	std::string buffer;
	std::string tempMidData;
	std::string tempOutput;
	std::unique_ptr<std::ofstream> tempBufferFile;
	tempBufferFile = std::make_unique<std::ofstream>(tempFilePath);
	bool isEndLine = false;
	bool isComma = false;
	bool isClearStart = true;

	if (tempBufferFile->is_open()) {
		*tempBufferFile << "dcConsData = [";
		entryList.empty() == true ? isClearStart = true : isClearStart = false;
		
		//���� uint ���ʿ� ����! warning ���� �߰�.
		for (unsigned int i = 0; i < fileListVector.size(); i++) {
			if (!isClearStart && isComma) {
				tempBufferFile->write(",", 1);
			}
			tempBufferFile->write("\n", 1);
			isClearStart = false;
			isComma = true;
			buffer = ConvertInputManager(fileListVector[i]);
			*tempBufferFile << buffer;
		}

		*tempBufferFile << "\n ];";
		//??? �̷��� �ǳ�?

		tempBufferFile->close();
		return true;
	}
	return false;
}


bool BBCCListFileEditor::CopyCompareList() {
	try {
		std::unique_ptr<std::fstream> dcconEntry;
		dcconEntry = std::make_unique<std::fstream>(entryPath, std::ios::out | std::ios::trunc);

		std::unique_ptr < std::ifstream> tempEntry;
		tempEntry = std::make_unique<std::ifstream>(tempFilePath);

		std::string buffer;

		dcconEntry->seekg(0);
		while (!tempEntry->eof()) {
			std::getline(*tempEntry, buffer);
			*dcconEntry << buffer << std::endl;
		}

		tempEntry->close();
	}
	catch (std::exception e) {		//���н� �ٷ� false ����
		return false;
	}
	//���� ���� �Ϸ�� �ӽ� ���� ���� �� true ����
	remove(tempFilePath.c_str());
	return true;
}

bool BBCCListFileEditor::ListReaderStart(std::string input) {
	return fileListReader->ListReaderEngineStarter(input);
}

int BBCCListFileEditor::LoadFileList() {
	fileListVector = fileListReader->ListPrinter();
	std::cout << "�� " << fileListVector.size() << "���� ������ �νĵǾ����ϴ�." << std::endl;
	return fileListVector.size();
}

std::vector<std::string> BBCCListFileEditor::ListReadingList() {	
	if (fileListVector.empty() == true) {
		std::cout << "List is empty!" << std::endl;
	}
	return fileListVector;
}



std::string BBCCListFileEditor::ConvertToUTF8(std::string input) {
	//���� c_str ���� ���ִ°� ������ ������ ���̴°� ������...
	//1. input string ���븸 �ٲ� ��� : ���� ���µ� ������
	//2. c_str ��ȯ�� ���� ���� ȣ���ϰų�, Char * ������ ��ȯ�� �����͸� �۾��ؾ��ϴ°��
	// = char * ���ڿ� ������ ���� �����ؼ� �������� ��.
	//������ 1�� ���̽��ΰ� �����Ƿ� �� ���Ĵ�� ����.
	//�ٵ� �� ¥�� iconv ����Ҷ� char * ����ؾ��ؼ�...
	
	iconv_t changer;
	changer = iconv_open("UTF-8", "CP949");

	char deString[256] = { 0, };
	char* dest = deString;

	const char* originalResource = input.c_str();

	size_t stLen = (strlen(input.c_str()) + 1) * sizeof(char);
	size_t dsLen = 255;

	if (changer != (iconv_t)(-1))
		iconv(changer, &originalResource, &stLen, &dest, &dsLen);

	std::string answer(deString);

	iconv_close(changer);

	return answer;
}
std::string BBCCListFileEditor::ConvertInputManager(std::string input) {
	std::string convertString = ConvertToUTF8(input);
	//std::string convertString = input;
	std::string answer;
	answer = "\t{name:\"" + convertString + "\",\t keywords:[\"" + convertString.substr(0, convertString.size() - EXT_LENGTH) + "\"], \t tags:[]}";
	return answer;
}
bool BBCCListFileEditor::Clear() {
	fileListVector.clear();
	return BBCCListFileReader::Clear();
}