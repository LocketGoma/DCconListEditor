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
		std::cout << "����Ʈ ������ ��γ� ������ �߸��Ǿ����ϴ�." << std::endl;
		return false;
	}

	ChangeReady();
	if (ParseEntry() == false) {
		std::cout << "������ ������ �Ϻΰ� �߸��Ǿ����ϴ�." << std::endl;
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