#pragma once
#include "resource.h"

#include <vector>
#include <filesystem>	//C++17

namespace fs = std::filesystem;

void list_reader();
void list_reader(string path);

#ifdef DEBUG
void list_tester();
void dccon_list_print();
#endif
