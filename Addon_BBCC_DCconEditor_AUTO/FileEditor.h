#pragma once
#include "resource.h"

#include <fstream>
#include <locale>
#include <cstdio>
#include <algorithm>

class FileListEditor(){
	
}

void entry_maker();
bool entry_parser();							//while문 안의 반복 함수
string convert_to_cp949(const char * input);	//UTF-8 to CP949
string convert_to_UTF8(const char * input);
string covert_input_manager(string input);


bool linking(string route);
int comparison();
void list_entry_writer();
int list_entry_printer();
void list_entry_copier();
void list_entry_writer_ASC();



#ifdef DEBUG
void entry_test();
#endif // DEBUG

