#pragma once
#include "resource.h"

#include <filesystem>	//C++17
#include <typeinfo>

namespace fs = std::filesystem;

class FileListReader(){
}



void list_reader();
bool list_reader(string path);

bool list_loaded();
int dccon_list_print();

#ifdef DEBUG
void list_tester();
void dccon_list_print();
#endif
