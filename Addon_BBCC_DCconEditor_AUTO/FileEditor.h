#pragma once
#include "resource.h"

#include <fstream>
#include <locale>



void entry_maker();
bool entry_parser();							//while�� ���� �ݺ� �Լ�
string convert_to_cp949(const char * input);	//UTF-8 to CP949
string convert_to_UTF8(const char * input);
string covert_input_manager(string input);




#ifdef DEBUG
void entry_test();
#endif // DEBUG

