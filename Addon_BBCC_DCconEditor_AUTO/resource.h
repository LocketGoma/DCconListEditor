#pragma once
//���� ���� �����
#include <iostream>
#include <string>
#include <map>


using namespace std;

/*	�������
*	dccon_list.js �� �� �ִ� ����� ����Ʈ = ����� ��Ʈ��
*	dccon ������ �� �ִ� ����� ����Ʈ = ����� ����Ʈ
*	��, entry : dccon_list.js���� ��� / list : ���� ����� ����Ʈ ��� 
*	���� ���ø� �˴ϴ�.
*/

/*	��������
*	0.1 : CUI ���� �ʱ���� ������.
*/

/*	���� ����/���� ����
*	1. GUI ���� ������
*/


//����� ���� ��
#define spaceline '    '	//�⺻ ����
#define name_length 8	//���� �̸� ���� (Ȯ���� ����)
#define ext_length 4		//Ȯ���� ����
#define retry_count 3	//�б� ���� �� ��õ� ȸ��
#define DEBUG

const string valid_ext_list[3] = { ".jpg",".gif",".png" };
