#pragma once
//사용될 공용 헤더들
#include <iostream>
#include <string>
#include <map>
#include <vector>

// ListEditor에서 사용중인 예약변수들
#define SPACELINE '    '	//기본 간격
#define NAME_LENGTH 8		//파일 이름 길이 (확장자 제외)
#define EXT_LENGTH 4		//확장자 길이
#define EXT_COUNT 3			//검사할 확장자 개수
#define RETRY_COUNT 3		//읽기 실패 시 재시도 회수
//#define DEBUG