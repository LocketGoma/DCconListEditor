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
		std::cout << "리스트 파일의 경로나 파일이 잘못되었습니다." << std::endl;
		return false;
	}
	if (ParseEntry() == false) {
		std::cout << "파일의 내용중 일부가 잘못되었습니다." << std::endl;
		return false;
	}
	return true;
}

//여기가 제에ㅔ에에에에에일느림
bool BBCCListFileEditor::Comparison() {	
	//리스트 엔트리
	int listEntrySize = entryList.size();

	//파일 리스트
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
//제일 중요하고 조심해야하는 부분
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

		//??? 이래도 되나?


		tempBufferFile->close();
		return true;
	}

}

std::string BBCCListFileEditor::ConvertToUTF8(std::string input) {
	//각각 c_str 선언 해주는게 나을까 변수에 붙이는게 나을까...
	//1. input string 내용만 바뀔 경우 : 지금 상태도 괜찮음
	//2. c_str 변환된 값을 자주 호출하거나, Char * 변수로 변환한 데이터를 작업해야하는경우
	// = char * 문자열 포인터 변수 선언해서 사용해줘야 됨.
	//지금은 1번 케이스인것 같으므로 현 형식대로 쓴다.
	//근데 뭐 짜피 iconv 사용할때 char * 사용해야해서...
	
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