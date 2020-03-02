#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#pragma once
#include "EngineHeader.h"
//타 프로그램에서도 쓸 수 있는 구조로 작성할것.
//C++ 17에서 작동함.
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

