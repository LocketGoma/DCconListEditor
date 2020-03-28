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
	void DisplayMenu();			//�޴� ���� ��
	//bool SelectMenu(int input);			//����ġ�� �� ��
	bool SelectMenu(std::istream &input);			//����ġ�� �� ��

	void LoadFileList();		//���� ����Ʈ �ε�
	void LoadEntryList();		//���� ��Ʈ�� �ε�
	void PrintFileList();		//���� ����Ʈ �����ֱ�
	void PrintEntryList();		//���� ��Ʈ�� �����ֱ�
	void MatchListAndEntry();	//����Ʈ�� ��Ʈ�� ��Ī
	void EditEntryList();		//���� ��Ʈ�� ����.

	inline bool CheckReady() { return statusListLoad == statusEntryLoad == true; }

	//�Ϻη� �⺻ ��Ģ�� ��� : status�� ������ �� �ֵ���.
	bool statusListLoad;		//����Ʈ �ε� ����
	bool statusEntryLoad;		//��Ʈ�� �ε� ����
	bool statusReady;			//���� �غ�?

	static inline int ChangeToInt(int input) {return (input > 47 && input < 58) ? input - 48 : -1; }

};

