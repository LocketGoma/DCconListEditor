#include "FileListReader.h"

bool FileListReader::ListReaderEngineStarter(std::string input) {	
	if (input.empty() == true) {
		path = "images/dccon";
	}
	else {
		path = input;
	}
	return FileListReadingEngine(path);
}


bool FileListReader::FileListReadingEngine(std::string path) {
	try {
		for (const auto& entry : fs::directory_iterator(path)) {
			//�ٿ��� ������ �ߴµ� �������� �ʹ� ������
			std::string temp = entry.path().string().substr(path.size() + 1);
			for (int i = 0; i < EXT_COUNT; i++) {
				if (valid_ext_list[i].compare(temp.substr(temp.size() - EXT_LENGTH)) == 0) {
					fileList.insert(std::pair<std::string, bool>(temp, false));
				}
			}
		}
	}
	catch (fs::filesystem_error e) {
		std::cout<<"��ΰ� �߸��Ǿ����ϴ�. ���� ��θ� �������ּ���." << std::endl;
		return false;
	}
	if (fileList.empty()) {
		std::cout << "��ο� ���ǿ� �´� ������ �������� �ʽ��ϴ�." << std::endl;
		return false;
	}
	fileListIter = fileList.begin();
	
	return true;
}

std::vector<std::string> FileListReader::ListPrinter() {
	std::vector<std::string> fileListString;

	if (fileList.empty() == true) {
		std::cout << "���� ����Ʈ�� ����ֽ��ϴ�." << std::endl;	
	}
	else {
		for (fileListIter = fileList.begin(); fileListIter != fileList.end(); fileListIter++) {
			fileListString.push_back(fileListIter->first);
		}
	}
	return fileListString;
}

bool FileListReader::Clear() {
	fileList.clear();

	return fileList.empty();
}