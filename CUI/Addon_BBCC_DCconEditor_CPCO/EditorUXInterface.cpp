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
			//std::cout << "\t\t 7. 리스트 정렬 (1~2를 실시한 후 실행해주세요) " << std::endl;
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
		std::cout << "파일 수정을 시작합니다." << std::endl;
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
		std::cout << "자동 정렬기능은 현재 재 개발중입니다." << std::endl;
		break;
	}
	case 7: {
		std::cout << "해당 기능은 현재 작동하지 않습니다." << std::endl;
		break;
	}
	case 8: {
		return false;
		break;
	}
	case 9: {
		std::cout << "파일 수정을 자동으로 수행합니다." << std::endl;
		AutoEntryEditor();
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
	int listcount = listEditor->LoadFileList();	

	statusReady = listEditor->TryCompareList();
}
void EditorUXInterface::EditEntryList() {
	MatchListAndEntry();
	if (statusReady == true) {
		switch (listEditor->EditEntryFile()) {
			case 1: {
				std::cout << "파일 리스트가 비어있습니다." << std::endl;
				break;
			}
			case 2: {
				std::cout << "파일 리스트 비교 도중 이상이 발생하였습니다." << std::endl;
				break;
			}
			case 3: {
				std::cout << "임시파일 생성 도중 이상이 발생하였습니다." << std::endl;
				break;
			}
			case 4: {
				std::cout << "엔트리 파일 수정 도중 이상이 발생하였습니다." << std::endl;
				break;
			}
			case 0: {
				std::cout << "파일 수정이 완료되었습니다." << std::endl;
				break;
			}
			default: {
				std::cout << "예기치 못한 문제가 발생하였습니다. \n출력된 에러메시지를 개발자에게 알려주세요." << std::endl;
				break;
			}
		}
	}
	else {
		std::cout << "파일 수정 준비가 완료되지 않았습니다." << std::endl;
	}
	
}
void EditorUXInterface::AutoEntryEditor() {
	if (statusReady == false) {
		listEditor->Clear();

		if (listEditor->ListReaderStart("images/dccon") == false) {
			std::cout << "파일 목록을 읽는데 실패하였습니다." << std::endl;
			return;
		}
		statusListLoad = true;
		if (listEditor->LinkingList("lib/dccon_list.js") == false) {
			std::cout << "디시콘 엔트리 파일을 읽는데 실패하였습니다." << std::endl;
			return;
		}
		statusEntryLoad = true;
	}

	EditEntryList();
	
}


int main() {
	EditorUXInterface *test = new EditorUXInterface();

	test->Starter();

}