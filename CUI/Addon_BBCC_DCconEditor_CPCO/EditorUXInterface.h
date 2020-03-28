#pragma once
#include "BBCCListFileEditor.h"
#include <string>
#include <cstdlib>
#include <conio.h>
#include <vector>


class EditorUXInterface
{
public :
	EditorUXInterface();
	void Starter();


private :
	std::unique_ptr<BBCCListFileEditor> listEditor;
	void DisplayMenu();			//메뉴 보일 곳
	//bool SelectMenu(int input);			//스위치문 들어갈 곳
	bool SelectMenu(std::istream &input);			//스위치문 들어갈 곳

	void LoadFileList();		//파일 리스트 로드
	void LoadEntryList();		//파일 엔트리 로드
	void PrintFileList();		//파일 리스트 보여주기
	void PrintEntryList();		//파일 엔트리 보여주기
	void MatchListAndEntry();	//리스트와 엔트리 매칭
	void EditEntryList();		//파일 엔트리 수정.

	inline bool CheckReady() { return statusListLoad == statusEntryLoad == true; }

	//일부러 기본 규칙을 어김 : status로 정렬할 수 있도록.
	bool statusListLoad;		//리스트 로드 상태
	bool statusEntryLoad;		//엔트리 로드 상태
	bool statusReady;			//수정 준비?

	static inline int ChangeToInt(int input) {return (input > 47 && input < 58) ? input - 48 : -1; }

};

