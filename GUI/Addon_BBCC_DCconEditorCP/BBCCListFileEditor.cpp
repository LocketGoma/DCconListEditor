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
	//���� c_str ���� ���ִ°� ������ ������ ���̴°� ������...
	//1. input string ���븸 �ٲ� ��� : ���� ���µ� ������
	//2. c_str ��ȯ�� ���� ���� ȣ���ϰų�, Char * ������ ��ȯ�� �����͸� �۾��ؾ��ϴ°��
	// = char * ���ڿ� ������ ���� �����ؼ� �������� ��.
	//������ 1�� ���̽��ΰ� �����Ƿ� �� ���Ĵ�� ����.
	//�ٵ� �� ¥�� iconv ����Ҷ� char * ����ؾ��ؼ�...
	
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