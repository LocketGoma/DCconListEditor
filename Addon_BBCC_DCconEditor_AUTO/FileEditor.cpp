#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include "FileEditor.h"
#include "addition/include/iconv.h"

extern map <string, bool> name_list;	//디시콘 이름 리스트. 이름 / 리스트 존재유무. 일단 wstring 말고 string으로 하고, 노멀 string이 문제생길시 wstring으로 교체할것.
extern map <string, bool>::iterator list_iter;


map <string, int> entry_list;		//파일에 있는 아이콘 리스트를 기록하는 map 자료형. 이름 / 파일 존재 유무 (0 : 리스트에만 있고 파일 없음 / 1 : 파일-리스트 일치 / 2~ : 중복된 이름의 파일 존재)
map <string, int>::iterator entry_iter = entry_list.begin();



/*'dccon_list.js 파일을 읽고, 수정하는 목적.*/
/*사실상 메인 코드*/
//map <string, int> entry_list;
string default_path = "lib/dccon_list.js";	//기본 경로
unique_ptr<fstream> dcconlist = make_unique<fstream>(default_path);

void entry_maker() {
	setlocale(LC_ALL, "korean");
	dcconlist->seekg(16);


	bool locker = true;
	while (locker==true) {
		locker = entry_parser();
	}
}
bool entry_parser() {
	string input;
	string midpoint;
	string output;
	getline(*dcconlist, input);
	if (dcconlist->fail() == true)
		return false;

	if (input.find("name") == string::npos)
		return false;
	midpoint = input.substr(input.find("name") + 6, input.find(""",") - (input.find("name") + 7));
	

	

	output = convert_to_cp949(midpoint.c_str());

#ifdef DEBUG
	cout << midpoint << endl;
	cout << output << endl;
#endif // DEBUG

	entry_list.insert(pair<string, int>(output, 0));

	return true;
}
string convert_to_cp949(const char * input) {
	iconv_t changer;
	changer = iconv_open("CP949", "UTF-8");

	char deString[256] = { 0, };
	char * dest = deString;

	const char * test = input;

	size_t stLen = (strlen(input) + 1) * sizeof(char);
	size_t dsLen = 255;

	if (changer != (iconv_t)(-1))
		iconv(changer, &test, &stLen, &dest, &dsLen);

	string answer(deString);

	iconv_close(changer);

	return answer;
}
string convert_to_UTF8(const char * input) {
	iconv_t changer;
	changer = iconv_open("UTF-8", "CP949");

	char deString[256] = { 0, };
	char * dest = deString;

	const char * test = input;

	size_t stLen = (strlen(input) + 1) * sizeof(char);
	size_t dsLen = 255;

	if (changer != (iconv_t)(-1))
		iconv(changer, &test, &stLen, &dest, &dsLen);

	string answer(deString);

	iconv_close(changer);

	return answer;
}
string covert_input_manager(string input) {
	string temp=convert_to_UTF8(input.c_str());
	string answer;
	answer = "\t{name:\"" + temp + "\",\t keywords:[\"" + temp.substr(0, temp.size() - ext_length) + "\"], \t tags:[]}";
	return answer;
}

int comparison() {
	int entry_size = entry_list.size();
	int list_size = name_list.size();
	
	
	try {
		for (list_iter = name_list.begin(); list_iter != name_list.end(); ++list_iter) {
			for (entry_iter = entry_list.begin(); entry_iter != entry_list.end(); ++entry_iter) {
				if (list_iter->first.compare(entry_iter->first) == 0) {
					list_iter->second = true;
					entry_iter->second++;
				}
			}
		}
	}
	catch (exception e) {
		return -1;
	}
	
#ifdef DEBUG
	for (entry_iter = entry_list.begin(); entry_iter != entry_list.end(); ++entry_iter) {
		cout << entry_iter->first << ":";
		cout << entry_iter->second << endl;
	}
	for (list_iter = name_list.begin(); list_iter != name_list.end(); ++list_iter) {
		cout << list_iter->first << ":";
		if (list_iter->second == true)
			cout << "true" << endl;
		else
		cout << "false" << endl;
	}
#endif //  

	return 1;

}
void list_entry_printer() {	//완성된 리스트를 쓰는 부분 (임시파일 생성)
	//일단 임시
	string temp;
	string midpoint;
	string output;
	ofstream ofile("test.txt");	//반드시 엔트리 오픈보다 나중에 실행될것.
	bool end_line = false;
	dcconlist->seekg(0);

	if (ofile.is_open()) {
		while (!dcconlist->eof()) {
			getline(*dcconlist, temp);
			//---비교부분
			if (temp.find("name") == string::npos) {
				if (end_line == true)
					break;

				ofile << temp;
				end_line = true;
				continue;
			}
			midpoint = temp.substr(midpoint.find("name") + 9, temp.find(""",") - (temp.find("name") + 7));
			output = convert_to_cp949(midpoint.c_str());
			cout << output << endl;
			entry_iter = entry_list.find(output);
				if (entry_iter != entry_list.end()) {
					if (entry_iter->second != 0) {
						if (end_line == true)
							ofile << endl;
						ofile << temp;
					}
					else {
						continue;
					}
			}
		}
		for (list_iter = name_list.begin(); list_iter != name_list.end(); ++list_iter) {
			if (list_iter->second == false) {
				ofile << "," << endl;
				string tp = covert_input_manager(list_iter->first);
				ofile << tp;
			}

		}
		
	}
	ofile << "\n"+temp << endl;



	ofile.close();

}

void list_entry_copier() {		//리스트 카피.
	ifstream ifile("test.txt");

	string temp;
	
	if (dcconlist->is_open()) {
		dcconlist->seekg(0);
		while (!ifile.eof()) {
			getline(ifile, temp);
			*dcconlist << temp << endl;
		}		
	}
	
	ifile.close();

	remove("test.txt");

}





#ifdef DEBUG
void entry_test() {
	if (dcconlist->is_open())
		cout << "opened" << endl;
	entry_maker();
	
	comparison();

	list_entry_printer();

	list_entry_copier();
	
	//else {
	/*
	string temp;
		ofstream ofile("test.txt");
		if (ofile.is_open()) {
			while (!dcconlist->eof()) {
				getline(*dcconlist, temp);
				ofile << temp << endl;
			}
			ofile.close();
		}

	*/
	//}
	
	//getline(*dcconlist, temp);
	//cout << temp << endl;

	
}

void dump()			//쓸지말지 버릴지 안버릴지 아직 못정한것들. 사용시 codecvt 헤더 필요, windows.h 헤더 필요.
{
	/*
	setlocale(LC_ALL, "korean");
	dcconlist->seekg(16);
	string temp;

	getline(*dcconlist, temp);
	cout << temp << endl;
	wchar_t cstr[256];
	char sstr[256] = {};
	MultiByteToWideChar(CP_UTF8, 0, temp.c_str(), -1, cstr, std::size(cstr));

	wstring bgs(cstr);
	string test;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	test = converter.to_bytes(bgs);

	string example = "40K극혐.png";
	cout << example.size() << endl;
	
	
	int i = 0;
	int j = 0;
	while (cstr[i] != '\0') {
		if (cstr[i] <= 0x7F) {
			sstr[j] = cstr[i];
			j++;
		}
		else {
			sstr[j] = 0x80 | ((cstr[i] >> 6) & 0x39);
			sstr[j + 1] = 0xD8 | (cstr[i] >> 6);

			j += 2;
		}
		i++;
	}
	sstr[j] = '\0';

	cout << sstr << endl;
	wcout << bgs << endl;

	*/

	//00111111 (=3F)

	//ADF9 -> B1 / D8
	//1010110111111001
	//1010110111 (6 shift)
	//10110111 (=B7) // | 0x80

	//10110001 (=B1)
	//11011000 (=D8)

	//D610 -> C7/F8
	//1101011000010000
	//1101011000 (6 shift)
	//11011000 (=D8)// | 0x80

	//11000111 (=C7)
	//11111000 (=F8)

}

#endif // DEBUG