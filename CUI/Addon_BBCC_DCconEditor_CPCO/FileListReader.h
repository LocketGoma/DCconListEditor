#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#pragma once
#include "EngineHeader.h"
//타 프로그램에서도 쓸 수 있는 구조로 작성할것.
//C++ 17에서 작동함.
#include <iostream>
#include <filesystem>
#include <typeinfo>
#include <map>
#include <string>

// ListEditor에서 사용중인 예약변수들
#define SPACELINE '    '	//기본 간격
#define NAME_LENGTH 8		//파일 이름 길이 (확장자 제외)
#define EXT_LENGTH 4		//확장자 길이
#define EXT_COUNT 3			//검사할 확장자 개수
#define RETRY_COUNT 3		//읽기 실패 시 재시도 회수

#if __cplusplus >= 201703L
namespace fs = std::filesystem;
#else

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

class FileListReader
{
	public:
		bool ListReaderEngineStarter(std::string input);
		std::vector<std::string> ListPrinter();

	private :
		const std::string valid_ext_list[3] = { ".jpg",".gif",".png" };
		std::map <std::string, bool> fileList;
		std::map <std::string, bool>::iterator fileListIter;		
			
		bool FileListReadingEngine(std::string path);		

};

