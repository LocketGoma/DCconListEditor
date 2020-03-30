#include "EditorUXInterface.h"

EditorUXInterface::EditorUXInterface() {
	statusListLoad = false;
	statusEntryLoad = false;
	statusReady = false;

	listEditor = std::make_unique<BBCCListFileEditor>();
}

void EditorUXInterface::Starter() {
	DisplayMenu();
}

void EditorUXInterface::DisplayMenu() {

	while (true) {
		try {
			system("cls");
			std::cout << "\n\t\tBBCC 디시콘 리스트 에디터\n\n" << std::endl;
			std::cout << "v0.65+\t\t\t\t\tmake by @locketgoma\n\n" << std::endl;
			std::cout << "현재 시스템 로드 상태 : 리스트 로드 - " << (statusListLoad == true ? "true" : "false");
			std::cout << " // 엔트리 로드 - " << (statusEntryLoad == true ? "true" : "false");
			std::cout << " // 파일 수정 준비 - " << (statusReady == true ? "완료" : "");
			std::cout << "\n리스트 : 실제 파일 목록을 의미 // 엔트리 : dccon_list.js 파일에 존재하는 디시콘 리스트를 의미" << std::endl;
			std::cout << "\n메뉴를 선택해주세요. :: \n\t\t 1. 디시콘 폴더 지정 // 2. Dccon_list.js 파일 지정 // 3. 편집 실행 " << std::endl;
			std::cout << "\t\t 4. 디시콘 리스트 출력 // 5. 디시콘 엔트리 출력" << std::endl;
			std::cout << "\t\t 7. 리스트 정렬 (1~2를 실시한 후 실행해주세요) " << std::endl;
			std::cout << "\t\t 8. 프로그램 종료 // 9. 전 잘 모르겠어요. (Auto Mode (v0.1) 실행)" << std::endl;

			if (SelectMenu(std::cin) == false) {
				break;
			}

		}
		catch (std::exception e) {
			std::cout << "치명적인 오류가 발생하였습니다." << std::endl;
			std::cout << e.what() << std::endl;
			std::cout << "위의 메세지를 개발자에게 알려주세요." << std::endl;
			break;
		}
	}
	std::cout << "프로그램을 종료합니다." << std::endl;
}
bool EditorUXInterface::SelectMenu(std::istream& input) {		
	switch (ChangeToInt(input.get()))
	{
	case 1: {
		std::cout << "디시콘 폴더 위치를 지정해주세요." << std::endl;
		std::cout << "형식 :: 'BBCC/images' " << std::endl;
		std::cout << "형식이 올바르지 않을 시 실행이 되지 않을 수 있습니다." << std::endl;
		std::cout << "취소를 원하신다면 exit를 입력해주세요." << std::endl;
		LoadFileList();
		break;
	}
	case 2: {
		std::cout << "디시콘 리스트 파일의 위치를 지정해주세요." << std::endl;
		std::cout << "형식 :: 'lib/dccon.js' " << std::endl;
		std::cout << "형식이 올바르지 않을 시 실행이 되지 않을 수 있습니다." << std::endl;
		std::cout << "취소를 원하신다면 exit를 입력해주세요." << std::endl;
		LoadEntryList();
		break;
	}
	case 3: {
		std::cout << "3" << std::endl;
		EditEntryList();
		break;
	}
	case 4: {
		std::cout << "파일 리스트 출력 : " << std::endl;
		PrintFileList();
		break;
	}
	case 5: {
		std::cout << "파일 엔트리 출력 : " << std::endl;
		PrintEntryList();
		break;
	}
	case 6: {
		std::cout << "6" << std::endl;
		break;
	}
	case 7: {
		std::cout << "7" << std::endl;
		break;
	}
	case 8: {
		return false;
		break;
	}
	case -1: {
		//error try-catch
		return true;
		break;
	}
	default:
		std::cout << "잘못된 입력입니다" << std::endl;
		break;
	}

	std::cout << "아무 버튼이나 눌러주세요." << std::endl;
	_getch();			//아무 입력용

	return true;
}
void EditorUXInterface::LoadFileList() {
	std::string route = "images/dccon";
	std::cin >> route;

	while (true) {
		if (route == "EXIT" || route == "exit") {
			break;
		}
		else if (listEditor->ListReaderStart(route) == true){
			statusListLoad = true;
			break;
		}
		else {
			std::cout << "잘못된 경로입니다. 경로를 다시 입력해주세요." << std::endl;
			std::cout << "취소하고 메뉴로 돌아가기를 원할 시 'exit'를 입력해 주세요." << std::endl;
			std::cin >> route;
		}
	}
}

void EditorUXInterface::LoadEntryList() {
	std::string route = "lib/dccon_list.js";
	std::cin >> route;

	while (true) {
		if (route == "EXIT" || route == "exit") {
			break;
		}
		else if (listEditor->LinkingList(route) == true) {
			statusEntryLoad = true;
			break;
		}
		else {
			std::cout << "잘못된 경로입니다. 경로를 다시 입력해주세요." << std::endl;
			std::cout << "취소하고 메뉴로 돌아가기를 원할 시 'exit'를 입력해 주세요." << std::endl;
			std::cin >> route;
		}
	}
}
void EditorUXInterface::PrintFileList() {
	if (statusListLoad == true) {
		for (std::string var : listEditor->ListReadingList())
		{
			std::cout << var << std::endl;
		}
	}
}

void EditorUXInterface::PrintEntryList() {
	listEditor->PrintEntryList();
}

void EditorUXInterface::MatchListAndEntry() {
	statusReady = listEditor->TryCompareList();
}
void EditorUXInterface::EditEntryList() {
	MatchListAndEntry();
	if (statusReady == true) {
		listEditor->EditEntryFile();
	}
	else {
		std::cout << "파일 수정 준비가 완료되지 않았습니다." << std::endl;
	}
	
}


int main() {
	EditorUXInterface *test = new EditorUXInterface();

	test->Starter();

}