#include "Interface.h"

class DCCon_Editor {
	public :
		DCCon_Editor();
		DCCon_Editor(string route);

		void select_con_folder();
		void select_list();


	private :
		string con_route;
		string list_route;


};


void DCCon_Editor::select_list() {

	string default_test = "";
	assert(default_test != "dcConsData"); // ������ ����� �� dccon����Ʈ ������ �ƴҶ� ���� �߻�. <- �����δ� �������� ��� ���°����� ����� ����.
	
}





int main() {
#ifdef DEBUG
	list_tester();
	entry_test();
	
#endif // DEBUG
	system("pause");
	return 0;
}

