#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#pragma once
#include "EngineHeader.h"
//Ÿ ���α׷������� �� �� �ִ� ������ �ۼ��Ұ�.
//C++ 17���� �۵���.
#include <iostream>
#include <filesystem>
#include <typeinfo>
#include <string>

#if __cplusplus >= 201703L
namespace fs = std::filesystem;
#else

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

class FileListReader
{
	public:
		void ListReaderEngineStarter(std::string input);
		std::vector<std::string> ListPrinter();

	private :
		const std::string valid_ext_list[3] = { ".jpg",".gif",".png" };
		std::map <std::string, bool> fileList;
		std::map <std::string, bool>::iterator fileListIter;		
			
		bool FileListReadingEngine(std::string path);
		

};

