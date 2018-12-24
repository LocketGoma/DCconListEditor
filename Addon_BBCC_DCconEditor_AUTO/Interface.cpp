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
	assert(default_test != "dcConsData"); // 파일이 제대로 된 dccon리스트 파일이 아닐때 에러 발생. <- 실제로는 유저에게 경고를 띄우는것으로 변경될 예정.
	
}





int main() {
#ifdef DEBUG
	list_tester();
	entry_test();
	
#endif // DEBUG
	system("pause");
	return 0;
}

