#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include "FileEditor.h"
#include "addition/include/iconv.h"

extern map <string, bool> name_list;	//����� �̸� ����Ʈ. �̸� / ����Ʈ ��������. �ϴ� wstring ���� string���� �ϰ�, ��� string�� ��������� wstring���� ��ü�Ұ�.
extern map <string, bool>::iterator list_iter;


map <string, int> entry_list;		//���Ͽ� �ִ� ������ ����Ʈ�� ����ϴ� map �ڷ���. �̸� / ���� ���� ���� (0 : ����Ʈ���� �ְ� ���� ���� / 1 : ����-����Ʈ ��ġ / 2~ : �ߺ��� �̸��� ���� ����)
map <string, int>::iterator entry_iter = entry_list.begin();



/*'dccon_list.js ������ �а�, �����ϴ� ����.*/
/*��ǻ� ���� �ڵ�*/
//map <string, int> entry_list;
string default_path = "lib/dccon_list.js";	//�⺻ ���
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
void list_entry_printer() {	//�ϼ��� ����Ʈ�� ���� �κ� (�ӽ����� ����)
	//�ϴ� �ӽ�
	string temp;
	string midpoint;
	string output;
	ofstream ofile("test.txt");	//�ݵ�� ��Ʈ�� ���º��� ���߿� ����ɰ�.
	bool end_line = false;
	dcconlist->seekg(0);

	if (ofile.is_open()) {
		while (!dcconlist->eof()) {
			getline(*dcconlist, temp);
			//---�񱳺κ�
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

void list_entry_copier() {		//����Ʈ ī��.
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

void dump()			//�������� ������ �ȹ����� ���� �����Ѱ͵�. ���� codecvt ��� �ʿ�, windows.h ��� �ʿ�.
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

	string example = "40K����.png";
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