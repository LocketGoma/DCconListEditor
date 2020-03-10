#include "BBCCListFileEditor.h"





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

	ChangeReady();
	if (ParseEntry() == false) {
		std::cout << "파일의 내용중 일부가 잘못되었습니다." << std::endl;
		return false;
	}
	else {
		ChangeEnd();
	}

	return true;
}

std::string BBCCListFileEditor::ConvertToUTF8(std::string input) {



}
std::string BBCCListFileEditor::ConvertInputManager(std::string input) {

}