#include "BBCCListFileReader.h"



//�⺻��
bool BBCCListFileReader::LinkingList(std::string route) {
	
	if (LoadEntry(route) == false) {
		std::cout << "����Ʈ ������ ��γ� ������ �߸��Ǿ����ϴ�." << std::endl;
		return false;
	}	
	if (ParseEntry() == false) {
		std::cout << "������ ������ �Ϻΰ� �߸��Ǿ����ϴ�." << std::endl;
		return false;
	}

	return true;
}
bool BBCCListFileReader::LoadEntry(std::string path) {
	setlocale(LC_ALL, "korean");

	try {
		dcconEntry = std::make_unique<std::fstream>(path);
	}
	catch (std::exception e){
		return false;
	}

	std::string testString;
	std::getline(*dcconEntry, testString);
	if (testString.substr(0, 10) == "dcConsData") {
		return true;
	}
	else {
		return false;
	}
}

bool BBCCListFileReader::ParseEntry() {	
	if (dcconEntry == nullptr || dcconEntry->fail() == true) {
		return false;
	}
	dcconEntry->seekg(16);

	std::string tempInput;
	std::string tempMidData;
	std::string tempOutput;

	while (!dcconEntry->eof()) {
		std::getline(*dcconEntry, tempInput);
		if (tempInput.find("name") == std::string::npos) { break; }
		tempMidData = tempInput.substr(tempInput.find("name") + 6, tempInput.find(""",") - (tempInput.find("name") + 7));
		tempOutput = ConvertToCP949(tempMidData);
		entryList.insert(std::pair<std::string, int>(tempOutput, 0));
	}
	std::cout<<entryList.size()<<std::endl;
	return true;
}
//wstring -> string
std::string BBCCListFileReader::ConvertToCP949(std::string input) {
	iconv_t changer;
	changer = iconv_open("CP949", "UTF-8");
	
	const char* originalResource = input.c_str();
	char deString[256] = {};	//�ִ�ġ ����
	char* dest = deString;
	size_t stLen = (strlen(originalResource) + 1 * sizeof(char));
	size_t dsLen = 256;

	if (changer != (iconv_t)(-1)) {
		iconv(changer, &originalResource, &stLen, &dest, &dsLen);
	}	

	iconv_close(changer);
	return std::string(deString);
}

bool BBCCListFileReader::PrintEntryList() {
	if (entryList.empty() == true) {
		std::cout << "��Ʈ���� ����ֽ��ϴ�." << std::endl;
		return false;
	}
	std::cout << "�� " << entryList.size() << "���� ��Ʈ���� Ȯ�εǾ����ϴ�." << std:: endl;

	for (entryListIter = entryList.begin(); entryListIter != entryList.end(); entryListIter++) {
		std::cout << entryListIter->first << std::endl;
	}
	return true;

}