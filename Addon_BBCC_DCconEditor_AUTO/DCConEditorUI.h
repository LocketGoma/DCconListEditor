#pragma once
#include "FileEditor.h"
#include "filereader.h"
#include <assert.h>
#include <conio.h>

class DCConEditorUI {
public:
	DCConEditorUI();
	//DCConEditorUI(string route);

	void starter();				//���α׷� ���ۺ�.

private:
	unique_ptr<FileListEditor> listEditor;

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


