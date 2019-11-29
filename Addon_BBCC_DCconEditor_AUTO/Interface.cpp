#include "Interface.h"



class DCCon_Editor {
	public :
		DCCon_Editor();
		//DCCon_Editor(string route);


		void starter();				//���α׷� ���ۺ�.


	private :
		void display();				//��º�
		bool select_menu(int input);//�޴�����
		void select_list(string);			//����� ����Ʈ �ε�
		void select_entry(string);		//����� ��Ʈ�� �ε�
		string list_route;			//����� ����Ʈ ���
		string entry_route;			//����� ��Ʈ�� ���
		void list_print();			//����� ����Ʈ ���
		void entry_print();			//����� ��Ʈ�� ���


		bool list_entry_match();	//����� ����Ʈ/��Ʈ�� ��Ī
		void list_entry_editor();
		bool list_entry_writer_ASCN();	//����� ����Ʈ/��Ʈ�� ����


		bool status_list_load;
		bool status_entry_load;
		bool status_ready;
		
};

DCCon_Editor::DCCon_Editor() {
	status_list_load = false;
	status_entry_load = false;
	status_ready = false;
	list_route = "images/dccon";
	entry_route = "lib/dccon_list.js";
}


void DCCon_Editor::starter() {
	this->display();
}

void DCCon_Editor::display() {

	int input = 8;

	while (true) {
		system("cls");
		cout << "\n\t\tBBCC ����� ����Ʈ ������\n\n" << endl;
		cout << "v0.57\t\t\t\t\tmake by @locketgoma\n\n" << endl;
		cout << "���� �ý��� �ε� ���� : ����Ʈ �ε� - " << (status_list_load==1 ? "true" : "false");
		cout << " // ��Ʈ�� �ε� - " << (status_entry_load==1 ? "true" : "false");
		cout << " // ���� ���� �غ� - " << (status_ready ==1 ? "�Ϸ�" : "");
		cout << "\n����Ʈ : ���� ���� ����� �ǹ� // ��Ʈ�� : dccon_list.js ���Ͽ� �����ϴ� ����� ����Ʈ�� �ǹ�" << endl;
		cout << "\n�޴��� �������ּ���. :: \n\t\t 1. ����� ���� ���� // 2. Dccon_list.js ���� ���� // 3. �� ���� "<<endl;
		cout << "\t\t 4. ����� ����Ʈ ��� // 5. ����� ��Ʈ�� ��� // 6. ���� ����" << endl;
		cout << "\t\t 7. ����Ʈ ���� (1~3�� �ǽ��� �� �������ּ���) " << endl;
		cout << "\t\t 8. ���α׷� ���� // 9. �� �� �𸣰ھ��. (Auto Mode (v0.1) ����)" << endl;
		

		cin >> input;
		
		
		if (!select_menu(input))
			break;

	}
	cout << "���α׷��� �����մϴ�." << endl;
	
}

bool DCCon_Editor::select_menu(int input) {
	string route;
	switch (input)
	{
		case 1 : {
			cout << "����� ���� ��ġ�� �������ּ���" << endl;
			cout << "���� :: 'BBCC/images'";
			cout << "������ �ùٸ��� ���� �� ������ ���� ���� �� �ֽ��ϴ�.\n" << endl;
			
			cin >> route;
			select_list(route);

			break;
		};
		case 2 : {
			cout << "\nDccon_list.js ���� ��θ� �˷��ּ���" << endl;
			cout << "(�⺻ ���� ��θ� ��� �� 'default_path' �� �Է����ּ���." << endl;			
			cin >> route;
			select_entry(route);
			break;
		};
		case 3: {
			if (status_list_load == status_entry_load && status_entry_load == true) {
				status_ready =list_entry_match();
			}
			else
				cout << "���� �ε尡 ���� ���� ����Ʈ�� �����մϴ�." << endl;
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
				cout << "���� �غ� ���� �ʾҽ��ϴ�. �����Ȳ�� �ٽ� Ȯ�����ּ���." << endl;
			else
				list_entry_editor();
			break;
		}
		case 7: {
			if (status_ready != true)
				cout << "���� �غ� ���� �ʾҽ��ϴ�. �����Ȳ�� �ٽ� Ȯ�����ּ���." << endl;
			else {
				cout << "�ش� ��� �̿�� '�±�' ������ ������ �� �ֽ��ϴ�." << endl;
				cout << "������ ���Ͻø� Y�� �����ּ���. ::" << endl;
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
				cout << "�ڵ� �۾��� �����Ͽ����ϴ�. ���� ��� ��������� �̿����ּ���." << endl;
			else {
				list_entry_editor();			
			}

			break;
		};

		default: {
			cout << "�߸��� �Է��Դϴ�." << endl;
			break;
		}
	};
	cout << "�ƹ� ��ư�̳� �����ּ���." << endl;

	_getch();

	return true;
}

void DCCon_Editor::select_list(string route) {	

	while (!list_reader(route)) {
		cout << "\n�߸��� ����Դϴ�. �ٸ� ��θ� �Է����ּ���. " << endl;
		cout << "��� �� exit�� �Է����ּ���." << endl;
		cin >> route;

		if (route == "exit")
			return;
	}
	status_list_load = list_loaded();
	cout << "����Ʈ �ҷ����� �۾��� �Ϸ�Ǿ����ϴ�." << endl;
}
void DCCon_Editor::select_entry(string route) {

	while(true){
	if (route != "default_path" && route.length()>4)
		if (route.substr(route.size() - 3) != ".js") {
			if (route.substr(route.size() - 1) != "/")
				route += "/";
			route += "dccon_list.js";
		}

	if (linking(route))
		break;

	cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
	cout << "��� �� exit�� �Է����ּ���." << endl;

	cin >> route;
	if (route == "exit")
		return;
	}

	entry_maker();
	status_entry_load = true;
	cout << "��Ʈ�� �ҷ����� �۾��� �Ϸ�Ǿ����ϴ�." << endl;
}
void DCCon_Editor::list_print() {
	int temp;
	if (status_list_load == true) {
		temp = dccon_list_print();
		cout << "�� " << temp << "���� ������� �ֽ��ϴ�." << endl;
	}
	else
		cout << "����Ʈ�� ����ֽ��ϴ�." << endl;
}
void DCCon_Editor::entry_print() {
	int temp;
	if (status_entry_load == true) {
		temp = list_entry_printer();
		cout << "�� " << temp << "���� ������� ��Ʈ���� �ֽ��ϴ�." << endl;
	}
	else
		cout << "��Ʈ���� ����ֽ��ϴ�." << endl;
}
bool DCCon_Editor::list_entry_match() {
	if (comparison() == -1)
		return false;
	else
		return true;
}
void DCCon_Editor::list_entry_editor() {
	list_entry_writer();
	list_entry_copier();
	cout << "�۾��� �Ϸ�Ǿ����ϴ�." << endl;
}
bool DCCon_Editor::list_entry_writer_ASCN() {
	try {
		list_entry_writer_ASC();
		list_entry_copier();
	}
	catch (exception e) {
		cout << "���� �۾��� �����Ͽ����ϴ�." << endl;
		return false;
	}
	return true;
}




int main() {
#ifdef DEBUG
	list_tester();
	entry_test();
	
#endif // DEBUG
	DCCon_Editor editor;
	editor.starter();


	system("pause");
	return 0;
}

