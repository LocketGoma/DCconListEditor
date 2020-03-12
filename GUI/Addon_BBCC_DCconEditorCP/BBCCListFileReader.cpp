#include "BBCCListFileReader.h"



//기본형
bool BBCCListFileReader::LinkingList(std::string route) {
	
	if (LoadEntry(route) == false) {
		std::cout << "리스트 파일의 경로나 파일이 잘못되었습니다." << std::endl;
		return false;
	}	
	if (ParseEntry() == false) {
		std::cout << "파일의 내용중 일부가 잘못되었습니다." << std::endl;
		return false;
	}

	return true;
}
bool BBCCListFileReader::LoadEntry(std::string path) {
	std:setlocale(LC_ALL, "korean");

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

	while (tempInput.find("name") != std::string::npos) {
		std::getline(*dcconEntry, tempInput);
		tempMidData = tempInput.substr(tempInput.find("name") + 6, tempInput.find(""",") - (tempInput.find("name") + 7));

		tempOutput = ConvertToCP949(tempMidData);

		entryList.insert(std::pair<std::string, int>(tempOutput, 0));
	}
	return true;
}
//wstring -> string
std::string BBCCListFileReader::ConvertToCP949(std::string input) {
	iconv_t changer;
	changer = iconv_open("CP949", "UTF-8");
	
	const char* originalResource = input.c_str();
	char deString[256] = {};	//최대치 지정
	char* dest = deString;
	size_t stLen = (strlen(originalResource) + 1 * sizeof(char));
	size_t dsLen = 256;

	if (changer != (iconv_t)(-1)) {
		iconv(changer, &originalResource, &stLen, &dest, &dsLen);
	}	

	iconv_close(changer);
	return std::string(deString);
}

