#include "DCConEditorUI.h"

DCConEditorUI::DCConEditorUI() {
	status_list_load = false;
	status_entry_load = false;
	status_ready = false;
	listEditor = make_unique<FileListEditor>();
	list_route = "images/dccon";
	entry_route = "lib/dccon_list.js";
}


void DCConEditorUI::starter() {
	this->display();
}

void DCConEditorUI::display() {

	int input = 8;

	while (true) {
		try {
			system("cls");
			cout << "\n\t\tBBCC 디시콘 리스트 에디터\n\n" << endl;
			cout << "v0.65\t\t\t\t\tmake by @locketgoma\n\n" << endl;
			cout << "현재 시스템 로드 상태 : 리스트 로드 - " << (status_list_load == 1 ? "true" : "false");
			cout << " // 엔트리 로드 - " << (status_entry_load == 1 ? "true" : "false");
			cout << " // 파일 수정 준비 - " << (status_ready == 1 ? "완료" : "");
			cout << "\n리스트 : 실제 파일 목록을 의미 // 엔트리 : dccon_list.js 파일에 존재하는 디시콘 리스트를 의미" << endl;
			cout << "\n메뉴를 선택해주세요. :: \n\t\t 1. 디시콘 폴더 지정 // 2. Dccon_list.js 파일 지정 // 3. 비교 실행 " << endl;
			cout << "\t\t 4. 디시콘 리스트 출력 // 5. 디시콘 엔트리 출력 // 6. 편집 실행" << endl;
			cout << "\t\t 7. 리스트 정렬 (1~3을 실시한 후 실행해주세요) " << endl;
			cout << "\t\t 8. 프로그램 종료 // 9. 전 잘 모르겠어요. (Auto Mode (v0.1) 실행)" << endl;


			cin >> input;


			if (!select_menu(input))
				break;

		}
		catch (exception e) {
			cout << e.what() << endl;
			cout << "해당 메세지를 개발자에게 알려주세요" << endl;
			break;
		}
	}
	cout << "프로그램을 종료합니다." << endl;

}

bool DCConEditorUI::select_menu(int input) {
	string route;
	switch (input)
	{
	case 1: {
		cout << "디시콘 폴더 위치를 지정해주세요" << endl;
		cout << "형식 :: 'BBCC/images'";
		cout << "형식이 올바르지 않을 시 실행이 되지 않을 수 있습니다.\n" << endl;

		cin >> route;
		select_list(route);

		break;
	};
	case 2: {
		cout << "\nDccon_list.js 파일 경로를 알려주세요" << endl;
		cout << "(기본 설정 경로를 사용 시 'default_path' 를 입력해주세요." << endl;
		cin >> route;
		select_entry(route);
		break;
	};
	case 3: {
		if (status_list_load == status_entry_load && status_entry_load == true) {
			status_ready = list_entry_match();
		}
		else
			cout << "아직 로드가 되지 않은 리스트가 존재합니다." << endl;
		break;
	};
	case 4: {
		list_print();
		break;
	}
	case 5: {
		entry_print();
		break;
	}
	case 6: {
		if (status_ready != true)
			cout << "아직 준비가 되지 않았습니다. 진행상황을 다시 확인해주세요." << endl;
		else
			list_entry_editor();
		break;
	}
	case 7: {
		if (status_ready != true)
			cout << "아직 준비가 되지 않았습니다. 진행상황을 다시 확인해주세요." << endl;
		else {
			cout << "해당 기능 이용시 '태그' 정보가 삭제될 수 있습니다." << endl;
			cout << "실행을 원하시면 Y를 눌러주세요. ::" << endl;
			char tpyn;
			cin >> tpyn;
			if (tpyn == 'Y' || tpyn == 'y') {
				list_entry_writer_ASCN();
				break;
			}
			else
				break;
		}
		break;
	}
	case 8: {
		return false;
	}
	case 9: {
		select_list("images/dccon");
		select_entry("default_path");
		if (status_list_load == status_entry_load && status_entry_load == true)
			status_ready = list_entry_match();
		if (status_ready != true)
			cout << "자동 작업에 실패하였습니다. 직접 경로 지정방식을 이용해주세요." << endl;
		else {
			list_entry_editor();
		}

		break;
	};

	default: {
		cout << "잘못된 입력입니다." << endl;
		break;
	}
	};
	cout << "아무 버튼이나 눌러주세요." << endl;
	_getch();			//아무 입력용

	return true;
}

void DCConEditorUI::select_list(string route) {

	while (!list_reader(route)) {
		cout << "\n잘못된 경로입니다. 다른 경로를 입력해주세요. " << endl;
		cout << "취소 시 exit를 입력해주세요." << endl;
		cin >> route;

		if (route == "exit")
			return;
	}
	status_list_load = list_loaded();
	cout << "리스트 불러오기 작업이 완료되었습니다." << endl;
}
void DCConEditorUI::select_entry(string route) {

	while (true) {
		if (route != "default_path" && route.length() > 4)
			if (route.substr(route.size() - 3) != ".js") {
				if (route.substr(route.size() - 1) != "/")
					route += "/";
				route += "dccon_list.js";
			}

		if (listEditor->linking(route))
			break;

		cout << "잘못된 경로입니다. 다시 입력해주세요." << endl;
		cout << "취소 시 exit를 입력해주세요." << endl;

		cin >> route;
		if (route == "exit")
			return;
	}

	listEditor->entry_maker();
	status_entry_load = true;
	cout << "엔트리 불러오기 작업이 완료되었습니다." << endl;
}
void DCConEditorUI::list_print() {
	int temp;
	if (status_list_load == true) {
		temp = dccon_list_print();
		cout << "총 " << temp << "개의 디시콘이 있습니다." << endl;
	}
	else
		cout << "리스트가 비어있습니다." << endl;
}
void DCConEditorUI::entry_print() {
	int temp;
	if (status_entry_load == true) {
		temp = listEditor->list_entry_printer();
		cout << "총 " << temp << "개의 디시콘이 엔트리에 있습니다." << endl;
	}
	else
		cout << "엔트리가 비어있습니다." << endl;
}
bool DCConEditorUI::list_entry_match() {
	if (listEditor->comparison() == -1)
		return false;
	else
		return true;
}
void DCConEditorUI::list_entry_editor() {
	listEditor->list_entry_writer();
	listEditor->list_entry_copier();
	cout << "작업이 완료되었습니다." << endl;
}
bool DCConEditorUI::list_entry_writer_ASCN() {
	try {
		listEditor->list_entry_writer_ASC();
		listEditor->list_entry_copier();
	}
	catch (exception e) {
		cout << "정렬 작업을 실패하였습니다." << endl;
		cout << "해당 메세지를 개발자에게 알려주세요 ::";
		cout << e.what() << endl;
		return false;
	}
	return true;
}




int main() {
#ifdef DEBUG
	list_tester();
	entry_test();

#endif // DEBUG
	DCConEditorUI editor;
	editor.starter();


	system("pause");
	return 0;
}

