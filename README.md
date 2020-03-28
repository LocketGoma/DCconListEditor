BBCC Addon : DCCon List Editor
===
version 0.6.5

해당 프로그램의 소스코드는 Visual Studio 2017 / C++17 이상에서만 정상작동을 보장합니다.

## 개요
해당 프로젝트는 트위치 확장 프로그램인 Bridge BBCC (https://github.com/krynen/BridgeBBCC) 프로젝트의 애드온으로 제작되는 프로젝트입니다.

현재 알파 테스트 빌드.


 * 2월 끝나기 전까지 WinAPI 입혀서 뜯어고칠 예정. <- 2월 내로 못끝날듯 ㅈㅅ <- 3월중 예정 ㅈㅅ
 
 * 최근 업데이트 : 클래스 Wrapping 작업 1차 완료


## 용어 정리
1. 디시콘 리스트 : '실제 디시콘 이미지 파일'들의 목록을 의미.

2. 디시콘 엔트리 : 'dccon_list.js' 파일에 들어가 있는 목록을 의미.


## 유의사항
코드 테스트 시 반드시 libiconv 라이브러리의 경로를 설정해줘야하고, C++ 빌드 버전을 C++17로 해야합니다. <- 다음 릴리즈때는 C++14도 사용가능하게 변경됩니다.


## Reference
https://github.com/pffang/libiconv-for-Windows

https://www.gnu.org/software/libiconv


## License
Depend on GNU libiconv [LGPL3.0]


## Special Thanks.
맛물님 (https://github.com/krynen), 네쓰윗님 (https://github.com/rishubil)


 [1]: https://www.gnu.org/licenses/lgpl.html
