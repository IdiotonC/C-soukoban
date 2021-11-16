#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#define UP    72 // 키보드 방향키 코드 이값 
#define DOWN   80 // 한번만 받으면 일반 h 같은거 충돌함
#define LEFT   75 
#define RIGHT   77 
#define SUBMIT 32
#define ESC 27 // 아스키 코드 ctrl + ecs == 27

using namespace std;

int x = 20; int y = 5; // 화면 중앙값 

char map[8][8] = {
	{00222000},
	{00212000},
	{00202222},
	{22230312},
	{21030222},
	{22223200},
	{00021200},
	{00022200},
}; //구조체로 하려고 했는데 잘 모르겠어서 땜빵해논 맵

typedef struct map
{
	char map[3];
}gamemap; // 게임맵 지정해주는 구조체 

int keyControll(void) {
	int scale = _getch();
	return scale;
} // 키 입력값 가져오는 곳 khbit 쓰고 싶었는데 흠 

void gotoxy(int x, int y) /*커서이동 함수 부분*/
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void init() {
	system("mode con cols=56 lines=20");  // 초기화면 초기화 함수
	
	HANDLE hConsole; // 커서 숨기는 콘솔커서 제어 함수 
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = 0; 
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int menuDraw() {
    int x = 24; int y = 12;
    int scale = 0;
        gotoxy(x - 2, y);
	    printf("▣게임시작");
	    gotoxy(x, y+1);
	    printf("게임 정보");
	    gotoxy(x, y+2);
	    printf("종료");
		while (true)
		{
			int menukey = keyControll();
			switch (menukey)
			{
			case UP: if (y > 12) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf("▣");
			}
				   break;
			case DOWN: if (y < 14) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf("▣");
			}
					 break;
			case SUBMIT:
				return y - 12;
			}
		}
}

void mapDraw() { 
	gotoxy(x, y++);
    printf("#      ##    ##   #####\n");
	gotoxy(x, y++);
    printf("#     #  #  #  #    #  \n");
	gotoxy(x, y++);
    printf("#     #  #  #  #    #  \n");
	gotoxy(x, y);
    printf("####   ##    ##     #  \n");
}

int information() {
	
	system("cls");
	char info[4][45] = {
		{"조작법"},{"이동 : ←,↑,↓,→"},{"선택: 스페이스바"},{"스페이스바를 누르면 메인화면으로 이동합니다."}
	};
	
	for (int i = 0; i <4; i++) {
		for (int j = 0; j < 45; j++) {
			printf("%c", info[i][j]);
		}
		printf("\n");
	}
	if (keyControll() == SUBMIT) {
		system("cls");
		return 0;
	}
}

int main() {
	init();
	while (true)
	{
		mapDraw();
		int menu = menuDraw();
		system("cls");
		switch (menu)
		{
		case 0:
			break;
		case 1: information();
			break;
		case 2:
			return 0;
		}
	}



	return 0;
}