#include "BBCCListFileReader.h"

bool BBCCListFileReader::LinkingList(std::string route) {
	std::string path = {};
	if (route.empty() == true) {
		path = "lib/dccon_list.js";
	}
	else {
		path = route;
	}

	if (LoadEntry(path) == false) {
		std::cout << "리스트 파일의 경로나 파일이 잘못되었습니다." << std::endl;
		return false;
	}

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
	if (dcconEntry == nullptr) {
		return false;
	}
	dcconEntry->seekg(16);

	std::string tempInput;
	std::string tempMidData;
	std::string tempOutput;


}
