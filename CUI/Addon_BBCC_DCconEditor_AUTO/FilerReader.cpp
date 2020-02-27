#include "filereader.h"
//'����� ����'���� ������̸� ��ϸ� �������� �κ�.


map <string, bool> name_list;	//����� �̸� ����Ʈ. �̸� / ����Ʈ ��������. �ϴ� wstring ���� string���� �ϰ�, ��� string�� ��������� wstring���� ��ü�Ұ�.
map <string, bool>::iterator list_iter;

void FileListReader::list_reader() {		//'�ϴ�' ������

	__cplusplus;
	string path = "images/dccon";	
	try {
		for (const auto & entry : fs::directory_iterator(path)) {			
			string temp = entry.path().string().substr(path.size() + 1);
			for (int i = 0; i < 3; i++) {
				if (valid_ext_list[i].compare(temp.substr(temp.size() - ext_length)) == 0)	//Ȯ���� Ȯ�� ��. 0�϶� ��� = ���
					name_list.insert(pair<string, bool>(temp, false));				
			}
		}
	}
	catch (fs::filesystem_error e) {
		cout << "��ΰ� �߸��Ǿ����ϴ�. ���������� ��ġ�� �������ּ���." << endl;
		return;
	}
	if (name_list.empty())
		cout << "����� ��ο� ���ǿ� �´� ������ �������� �ʽ��ϴ�." << endl;

	list_iter = name_list.begin();
}
bool FileListReader::list_reader(string path) {
	try {
		for (const auto & entry : fs::directory_iterator(path)) {
			string temp = entry.path().string().substr(path.size() + 1);
			for (int i = 0; i < 3; i++) {
				if (valid_ext_list[i].compare(temp.substr(temp.size() - ext_length)) == 0)	//Ȯ���� Ȯ�� ��
					name_list.insert(pair<string, bool>(temp, false));				
			}
		}
	}
	catch (fs::filesystem_error e) {
		cout << "��ΰ� �߸��Ǿ����ϴ�. ��θ� �� �������ּ���." << endl;
		return false;
	}
	if (name_list.empty()) {
		cout << "���ǿ� �´� ������ �������� �ʽ��ϴ�. ��θ� �� �������ּ���." << endl;
		return false;
	}


	list_iter = name_list.begin();
	return true;
}

bool FileListReader::list_loaded() {
	return name_list.empty() ? false : true;
}
int FileListReader::dccon_list_print() {
	for (list_iter = name_list.begin(); list_iter != name_list.end(); list_iter++) {
		cout << list_iter->first << endl;
	}
	return name_list.size();
}
	//����׿� �ڵ�
#ifdef DEBUG
void FileListReader::list_tester() {
	list_reader();

	//dccon_list_print();

}

#endif // DEBUG