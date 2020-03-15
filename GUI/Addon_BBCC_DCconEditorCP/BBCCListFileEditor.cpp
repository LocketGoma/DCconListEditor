#include "BBCCListFileEditor.h"

BBCCListFileEditor::BBCCListFileEditor() {
	fileListReader = std::make_unique<FileListReader>();
	fileListVector = fileListReader->ListPrinter();
}


bool BBCCListFileEditor::TryCompareList() {

	return Comparison();
}


bool BBCCListFileEditor::LinkingList(std::string route) {
	std::string path = {};
	if (route.empty() == true) {
		path = "lib/dccon_list.js";
	}
	else {
		path = route;
	}
	if (LoadEntry(path) == false) {
		std::cout << "����Ʈ ������ ��γ� ������ �߸��Ǿ����ϴ�." << std::endl;
		return false;
	}
	if (ParseEntry() == false) {
		std::cout << "������ ������ �Ϻΰ� �߸��Ǿ����ϴ�." << std::endl;
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
	catch (_exception e) {
		return false;
	}
}
//���� �߿��ϰ� �����ؾ��ϴ� �κ�
bool BBCCListFileEditor::ListEntryWriter() {
	std::string buffer;
	std::string tempMidData;
	std::string tempOutput;
	std::unique_ptr<std::ofstream> tempBufferFile;
	tempBufferFile = std::make_unique<std::ofstream>("temp.bat");
	bool isEndLine = false;
	bool isComma = false;
	bool isClearStart = true;


	if (tempBufferFile->is_open()) {
		tempBufferFile->write("dcConsData = [",sizeof(std::string)*16);
		entryList.empty() == true ? isClearStart = true : isClearStart = false;
		
		for (int i = 0; i < fileListVector.size(); i++) {
			if (!isClearStart && !isComma) {
				tempBufferFile->write(",", 1);
			}
			tempBufferFile->write("\n", 1);
			isClearStart = isComma = false;
			buffer = ConvertInputManager(fileListVector[i]);
			tempBufferFile->write(buffer.c_str(), sizeof(buffer));
		}

		//??? �̷��� �ǳ�?


		tempBufferFile->close();
		return true;
	}

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
	std::string answer;
	answer = "\t{name:\"" + convertString + "\",\t keywords:[\"" + convertString.substr(0, convertString.size() - EXT_LENGTH) + "\"], \t tags:[]}";
	return answer;
}