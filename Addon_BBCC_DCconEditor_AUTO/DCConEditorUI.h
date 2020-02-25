#pragma once
#include "FileEditor.h"
#include "filereader.h"
#include <assert.h>
#include <conio.h>

class DCConEditorUI {
public:
	DCConEditorUI();
	//DCConEditorUI(string route);

	void starter();				//프로그램 시작부.

private:
	unique_ptr<FileListEditor> listEditor;

	void display();				//출력부
	bool select_menu(int input);//메뉴선택
	void select_list(string);			//디시콘 리스트 로드
	void select_entry(string);		//디시콘 엔트리 로드
	string list_route;			//디시콘 리스트 경로
	string entry_route;			//디시콘 엔트리 경로
	void list_print();			//디시콘 리스트 출력
	void entry_print();			//디시콘 엔트리 출력


	bool list_entry_match();	//디시콘 리스트/엔트리 매칭
	void list_entry_editor();
	bool list_entry_writer_ASCN();	//디시콘 리스트/엔트리 정렬


	bool status_list_load;
	bool status_entry_load;
	bool status_ready;

};


