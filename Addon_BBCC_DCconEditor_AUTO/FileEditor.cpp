#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include "FileEditor.h"
#include "addition/include/iconv.h"




/*'dccon_list.js ������ �а�, �����ϴ� ����.*/
/*��ǻ� ���� �ڵ�*/

map <string, int> entry_list;		//���Ͽ� �ִ� ������ ����Ʈ�� ����ϴ� map �ڷ���. �̸� / ���� ���� ���� (0 : ����Ʈ���� �ְ� ���� ���� / 1 : ����-����Ʈ ��ġ / 2~ : �ߺ��� �̸��� ���� ����)
map <string, int>::iterator entryiter = entry_list.begin();
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

	midpoint = convert_to_cp949(input.c_str());
	cout << midpoint << endl;

	if (midpoint.find("name") == string::npos)
		return false;

	output = midpoint.substr(midpoint.find("name") + 6, midpoint.find(""",")-(midpoint.find("name") + 7));
	cout << output << endl;

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





#ifdef DEBUG
void entry_test() {
	entry_maker();
	
	string temp;

	if (dcconlist->is_open())
		cout << "opened" << endl;
	
	//else {
	/*
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

void dump()			//�������� ������ �ȹ����� ���� �����Ѱ͵�. 
{
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