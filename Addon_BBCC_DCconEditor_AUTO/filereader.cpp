#include "filereader.h"

#include <typeinfo>
//'디시콘 폴더'에서 디시콘이름 목록만 갖고오는 부분.

map <string,bool> name_list;	//디시콘 이름 리스트. 이름 / 리스트 존재유무. 일단 wstring 말고 string으로 하고, 노멀 string이 문제생길시 wstring으로 교체할것.
map <string, bool>::iterator list_iter = name_list.begin();

void list_reader() {		//'일단' 구현됨
	string path = "images/dccon";	
	try {
		for (const auto & entry : fs::directory_iterator(path)) {			
			string temp = entry.path().string().substr(path.size() + 1);
			for (int i = 0; i < 3; i++) {
				if (valid_ext_list[i].compare(temp.substr(temp.size() - ext_length)) == 0)	//확장자 확인 비교
					name_list.insert(pair<string, bool>(temp, false));				
			}
		}
	}
	catch (fs::filesystem_error e) {
		cout << "경로가 잘못되었습니다. 실행파일의 위치를 점검해주세요." << endl;
		return;
	}
	if (name_list.empty())
		cout << "예약된 경로에 조건에 맞는 파일이 존재하지 않습니다." << endl;

	list_iter = name_list.begin();
}
void list_reader(string path) {	
	try {
		for (const auto & entry : fs::directory_iterator(path)) {
			string temp = entry.path().string().substr(path.size() + 1);
			for (int i = 0; i < 3; i++) {
				if (valid_ext_list[i].compare(temp.substr(temp.size() - ext_length)) == 0)	//확장자 확인 비교
					name_list.insert(pair<string, bool>(temp, false));				
			}
		}
	}
	catch (fs::filesystem_error e) {
		cout << "경로가 잘못되었습니다. 경로를 재 지정해주세요." << endl;
		return;
	}
	if (name_list.empty())
		cout << "조건에 맞는 파일이 존재하지 않습니다. 경로를 재 지정해주세요." << endl;

	list_iter = name_list.begin();
}
	//디버그용 코드
#ifdef DEBUG
void list_tester() {
	list_reader();

	dccon_list_print();

}
void dccon_list_print() {
	for (; list_iter != name_list.end(); list_iter++) {
		cout << list_iter->first << endl;
	}
}
#endif // DEBUG
