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
			std::cout << "\n\t\tBBCC ����� ����Ʈ ������\n\n" << std::endl;
			std::cout << "v0.65+\t\t\t\t\tmake by @locketgoma\n\n" << std::endl;
			std::cout << "���� �ý��� �ε� ���� : ����Ʈ �ε� - " << (statusListLoad == true ? "true" : "false");
			std::cout << " // ��Ʈ�� �ε� - " << (statusEntryLoad == true ? "true" : "false");
			std::cout << " // ���� ���� �غ� - " << (statusReady == true ? "�Ϸ�" : "");
			std::cout << "\n����Ʈ : ���� ���� ����� �ǹ� // ��Ʈ�� : dccon_list.js ���Ͽ� �����ϴ� ����� ����Ʈ�� �ǹ�" << std::endl;
			std::cout << "\n�޴��� �������ּ���. :: \n\t\t 1. ����� ���� ���� // 2. Dccon_list.js ���� ���� // 3. ���� ���� " << std::endl;
			std::cout << "\t\t 4. ����� ����Ʈ ��� // 5. ����� ��Ʈ�� ���" << std::endl;
			//std::cout << "\t\t 7. ����Ʈ ���� (1~2�� �ǽ��� �� �������ּ���) " << std::endl;
			std::cout << "\t\t 8. ���α׷� ���� // 9. �� �� �𸣰ھ��. (Auto Mode (v0.1) ����)" << std::endl;

			if (SelectMenu(std::cin) == false) {
				break;
			}

		}
		catch (std::exception e) {
			std::cout << "ġ������ ������ �߻��Ͽ����ϴ�." << std::endl;
			std::cout << e.what() << std::endl;
			std::cout << "���� �޼����� �����ڿ��� �˷��ּ���." << std::endl;
			break;
		}
	}
	std::cout << "���α׷��� �����մϴ�." << std::endl;
}
bool EditorUXInterface::SelectMenu(std::istream& input) {		
	switch (ChangeToInt(input.get()))
	{
	case 1: {
		std::cout << "����� ���� ��ġ�� �������ּ���." << std::endl;
		std::cout << "���� :: 'BBCC/images' " << std::endl;
		std::cout << "������ �ùٸ��� ���� �� ������ ���� ���� �� �ֽ��ϴ�." << std::endl;
		std::cout << "��Ҹ� ���ϽŴٸ� exit�� �Է����ּ���." << std::endl;
		LoadFileList();
		break;
	}
	case 2: {
		std::cout << "����� ����Ʈ ������ ��ġ�� �������ּ���." << std::endl;
		std::cout << "���� :: 'lib/dccon.js' " << std::endl;
		std::cout << "������ �ùٸ��� ���� �� ������ ���� ���� �� �ֽ��ϴ�." << std::endl;
		std::cout << "��Ҹ� ���ϽŴٸ� exit�� �Է����ּ���." << std::endl;
		LoadEntryList();
		break;
	}
	case 3: {
		std::cout << "���� ������ �����մϴ�." << std::endl;
		EditEntryList();
		break;
	}
	case 4: {
		std::cout << "���� ����Ʈ ��� : " << std::endl;
		PrintFileList();
		break;
	}
	case 5: {
		std::cout << "���� ��Ʈ�� ��� : " << std::endl;
		PrintEntryList();
		break;
	}
	case 6: {
		std::cout << "�ڵ� ���ı���� ���� �� �������Դϴ�." << std::endl;
		break;
	}
	case 7: {
		std::cout << "�ش� ����� ���� �۵����� �ʽ��ϴ�." << std::endl;
		break;
	}
	case 8: {
		return false;
		break;
	}
	case 9: {
		std::cout << "���� ������ �ڵ����� �����մϴ�." << std::endl;
		AutoEntryEditor();
		break;
	}
	case -1: {
		//error try-catch
		return true;
		break;
	}
	default:
		std::cout << "�߸��� �Է��Դϴ�" << std::endl;
		break;
	}

	std::cout << "�ƹ� ��ư�̳� �����ּ���." << std::endl;
	_getch();			//�ƹ� �Է¿�

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
			std::cout << "�߸��� ����Դϴ�. ��θ� �ٽ� �Է����ּ���." << std::endl;
			std::cout << "����ϰ� �޴��� ���ư��⸦ ���� �� 'exit'�� �Է��� �ּ���." << std::endl;
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
			std::cout << "�߸��� ����Դϴ�. ��θ� �ٽ� �Է����ּ���." << std::endl;
			std::cout << "����ϰ� �޴��� ���ư��⸦ ���� �� 'exit'�� �Է��� �ּ���." << std::endl;
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
				std::cout << "���� ����Ʈ�� ����ֽ��ϴ�." << std::endl;
				break;
			}
			case 2: {
				std::cout << "���� ����Ʈ �� ���� �̻��� �߻��Ͽ����ϴ�." << std::endl;
				break;
			}
			case 3: {
				std::cout << "�ӽ����� ���� ���� �̻��� �߻��Ͽ����ϴ�." << std::endl;
				break;
			}
			case 4: {
				std::cout << "��Ʈ�� ���� ���� ���� �̻��� �߻��Ͽ����ϴ�." << std::endl;
				break;
			}
			case 0: {
				std::cout << "���� ������ �Ϸ�Ǿ����ϴ�." << std::endl;
				break;
			}
			default: {
				std::cout << "����ġ ���� ������ �߻��Ͽ����ϴ�. \n��µ� �����޽����� �����ڿ��� �˷��ּ���." << std::endl;
				break;
			}
		}
	}
	else {
		std::cout << "���� ���� �غ� �Ϸ���� �ʾҽ��ϴ�." << std::endl;
	}
	
}
void EditorUXInterface::AutoEntryEditor() {
	if (statusReady == false) {
		listEditor->Clear();

		if (listEditor->ListReaderStart("images/dccon") == false) {
			std::cout << "���� ����� �дµ� �����Ͽ����ϴ�." << std::endl;
			return;
		}
		statusListLoad = true;
		if (listEditor->LinkingList("lib/dccon_list.js") == false) {
			std::cout << "����� ��Ʈ�� ������ �дµ� �����Ͽ����ϴ�." << std::endl;
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