#include "BBCCListFileEditor.h"

BBCCListFileEditor::BBCCListFileEditor() {
	fileListReader = std::make_unique<FileListReader>();	
	tempFilePath = "temp.bat";

	entryPath = "lib/dccon_list.js";
}

//모든 리스트벡터를 리스트맵으로 변경시켜야 됨.
bool BBCCListFileEditor::MakeFileListMap(std::vector<std::string> fileList) {
	for (std::string fileName : fileList) {
		fileListMap.insert(std::pair<std::string, int>(fileName, 0));
	}
	return fileListMap.empty();
}



//일단 사용중지.
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
		std::cout << "엔트리 파일의 경로나 파일이 잘못되었습니다." << std::endl;
		return false;
	}
	if (ParseEntry() == false) {
		std::cout << "엔트리 파일의 내용중 일부가 잘못되었습니다." << std::endl;
		return false;
	}
	return true;
}

//여기가 제에ㅔ에에에에에일느림
bool BBCCListFileEditor::Comparison() {	
	//리스트 엔트리
	int listEntrySize = entryList.size();
	//파일 리스트
	int FileListSize = fileListMap.size();
	std::map<std::string, int>::iterator fileListiter;

	bool checkFlag = false;
	try {
		//1차 비교
		for (entryListIter = entryList.begin() ; entryListIter != entryList.end() ; ++entryListIter){
			for (fileListiter = fileListMap.begin(); fileListiter != fileListMap.end(); ++fileListiter) {
				if (fileListiter->first.compare(entryListIter->first) == 0) {
					checkFlag = true;
					++fileListiter->second;
					break;
				}
			}
			if (checkFlag == false) {
				entryList.erase(entryListIter->first);
			}
			checkFlag = false;
		}

		//2차 비교
		std::vector<std::string> temp;
		temp.push_back(fileListiter->first);
		for (fileListiter = fileListMap.begin(); fileListiter != fileListMap.end(); ++fileListiter) {
			if (fileListiter->second == 0) {

				entryList.insert(std::pair<std::string, std::vector<std::string>>(fileListiter->first, temp));
			}
		}
	}
	catch (std::exception e) {
		return false;
	}




	return true;
}
//이거 '파일 리스트에는 있는데 엔트리 리스트에는 없는 경우'가 잡히나?
//1. 파일 리스트에는 있으나 엔트리 리스트에는 없음	= ?
//2. 둘다 있음										= true
//3. 파일 리스트에는 없으나 엔트리 리스트에는 있음	= 삭제 대상.

//bool BBCCListFileEditor::Comparison(std::string compareString) {
//	//파일 리스트 = 실제 파일 목록들!
//	int FileListSize = fileListVector.size();
//	bool checkFlag = false;
//		for (int i = 0; i < FileListSize; i++) {
//				if (fileListVector[i].compare(compareString) == 0) {		//다르면 빼는 부분이 없어짐... 이면 할 필요가 있나?
//					return true;
//			}
//		}
//	return false;
//}

int BBCCListFileEditor::EditEntryFile() {	
	//0		: 정상
	//1		: 파일 리스트가 비어있음
	//2		: 리스트 비교시 이상
	//3		: 임시 파일 생성시 이상
	//4		: 임시 파일 복사시 이상
	//-1	: 그 외 오류
	try {
		if (fileListMap.empty() == true) {
			return 1;
		}
		//if (TryCompareList() == false) {
		//	return 2;
		//}
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

//제일 중요하고 조심해야하는 부분

//bool BBCCListFileEditor::ListEntryWriter() {
//	std::string buffer;
//	std::string tempMidData;
//	std::string tempOutput;
//	std::unique_ptr<std::ofstream> tempBufferFile;
//	tempBufferFile = std::make_unique<std::ofstream>(tempFilePath);
//	bool isEndLine = false;
//	bool isComma = false;
//	bool isClearStart = true;
//
//	if (tempBufferFile->is_open()) {
//		*tempBufferFile << "dcConsData = [";
//		entryList.empty() == true ? isClearStart = true : isClearStart = false;
//		
//
//
//		//굳이 uint 쓸필요 없음! warning 떠서 추가.
//		for (unsigned int i = 0; i < fileListVector.size(); i++) {
//			if (!isClearStart && isComma) {
//				tempBufferFile->write(",", 1);
//			}
//			tempBufferFile->write("\n", 1);
//			isClearStart = false;
//			isComma = true;
//
//			entryListIter = entryList.find(fileListVector[i]);
//			if (entryListIter != entryList.end()) {
//				buffer = ConvertInputManager(entryListIter->first, entryListIter->second);
//			}
//			else {
//				;
//			}
//
//
//			*tempBufferFile << buffer;
//		}
//
//		*tempBufferFile << "\n ];";
//		//??? 이래도 되나?
//
//		tempBufferFile->close();
//		return true;
//	}
//	return false;
//}
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

		//다시 짜시오.



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
	catch (std::exception e) {		//실패시 바로 false 리턴
		return false;
	}
	//정상 복사 완료시 임시 파일 삭제 후 true 리턴
	remove(tempFilePath.c_str());
	return true;
}

bool BBCCListFileEditor::ListReaderStart(std::string input) {
	return fileListReader->ListReaderEngineStarter(input);
}

int BBCCListFileEditor::LoadFileList() {
	MakeFileListMap(fileListReader->ListPrinter());
	std::cout << "총 " << fileListMap.size() << "개의 파일이 인식되었습니다." << std::endl;

	return fileListMap.size();
}

std::vector<std::string> BBCCListFileEditor::ReadingFileList() {	
	std::vector <std::string> fileListNames;
	if (fileListMap.empty() == true) {
		std::cout << "List is empty!" << std::endl;
	}
	for (auto &fileList : fileListMap) {
		fileListNames.push_back(fileList.first);
	}


	return fileListNames;
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
std::string BBCCListFileEditor::ConvertInputManager(std::string input, std::vector<std::string> tags) {
	std::string tagsLine;
	for (std::string tag : tags) {
		tagsLine += ("\"" + tag + "\",");
	}

	std::string convertString = ConvertToUTF8(input);
	std::string convertTags = ConvertToUTF8(tagsLine.substr(0, tagsLine.size() - 1));
	//std::string convertString = input;
	std::string answer;
	answer = "\t{name:\"" + convertString + "\",\t keywords:[\"" + convertString.substr(0, convertString.size() - EXT_LENGTH) + "\"], \t tags:[" + convertTags +"]}";
	return answer;
}
bool BBCCListFileEditor::Clear() {
	fileListMap.clear();
	return BBCCListFileReader::Clear();
}