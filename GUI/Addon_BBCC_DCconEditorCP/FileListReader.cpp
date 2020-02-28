#include "FileListReader.h"

void FileListReader::ListReaderEngineStarter(std::string input) {
	std::string path;
	if (input.empty() == true) {
		path = "images/dccon";
	}
	else {
		path = input;
	}
	ListReader(path);
}


bool FileListReader::ListReader(std::string path) {
	try {
		for (const auto& entry : fs::directory_iterator(path)) {
			//붙여서 쓰려고 했는데 가독성이 너무 떨어짐
			std::string temp = entry.path().string().substr(path.size() + 1);
			for (int i = 0; i < EXT_COUNT; i++) {
				if (valid_ext_list[i].compare(temp.substr(temp.size() - EXT_LENGTH)) == 0) {
					fileList.insert(std::pair<std::string, bool>(temp, false));
				}
			}
		}
	}
	catch (fs::filesystem_error e) {
		std::cout<<"경로가 잘못되었습니다. 폴더 경로를 점검해주세요." << std::endl;
		return false;
	}
	if (fileList.empty()) {
		std::cout << "경로에 조건에 맞는 파일이 존재하지 않습니다." << std::endl;
		false;
	}


}