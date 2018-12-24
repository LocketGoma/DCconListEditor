#pragma once
//사용될 공용 헤더들
#include <iostream>
#include <string>
#include <map>


using namespace std;

/*	용어정리
*	dccon_list.js 에 들어가 있는 디시콘 리스트 = 디시콘 엔트리
*	dccon 폴더에 들어가 있는 디시콘 리스트 = 디시콘 리스트
*	즉, entry : dccon_list.js파일 목록 / list : 실제 디시콘 리스트 목록 
*	으로 보시면 됩니다.
*/

/*	버전관리
*	0.1 : CUI 버전 초기버전 릴리즈.
*/

/*	예정 개발/개선 사항
*	1. GUI 버전 릴리즈
*/


//예약된 변수 등
#define spaceline '    '	//기본 간격
#define name_length 8	//파일 이름 길이 (확장자 제외)
#define ext_length 4		//확장자 길이
#define retry_count 3	//읽기 실패 시 재시도 회수
#define DEBUG

const string valid_ext_list[3] = { ".jpg",".gif",".png" };
