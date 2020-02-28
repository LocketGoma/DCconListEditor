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
		false;
	}


}