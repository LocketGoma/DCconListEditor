#pragma once
#include "resource.h"


#include <fstream>
#include <locale>
#include <vector>


void entry_maker();
bool entry_parser();							//while문 안의 반복 함수
string convert_to_cp949(const char * input);	//UTF-8 to CP949



#ifdef DEBUG
void entry_test();
#endif // DEBUG

