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
#define ESC 27 // 아스키 코드 ecs == 27

char map[][73] = {
	{"00222000n00212000n00202222n22234312n21030222n22223200n00021200n00022200n"},
	{"00222n00212n00202222n22230312n21030222n222202n000242n000222n"}
};

enum {
	BLACK, /* 0 : 까망 */
	DARK_BLUE, /* 1 : 어두운 파랑 */
	DARK_GREEN, /* 2 : 어두운 초록 */
	DARK_SKY_BLUE, /* 3 : 어두운 하늘 */
	DARK_RED, /* 4 : 어두운 빨강 */
	DARK_VIOLET, /* 5 : 어두운 보라 */
	DARK_YELLOW, /* 6 : 어두운 노랑 */
	GRAY, /* 7 : 회색 */
	DARK_GRAY, /* 8 : 어두운 회색 */
	BLUE, /* 9 : 파랑 */
	GREEN, /* 10 : 초록 */
	SKY_BLUE, /* 11 : 하늘 */
	RED, /* 12 : 빨강 */
	VIOLET, /* 13 : 보라 */
	YELLOW, /* 14 : 노랑 */
	WHITE, /* 15 : 하양 */
};
void setFontColor(int color)
{
	CONSOLE_SCREEN_BUFFER_INFO buff;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buff);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		(buff.wAttributes & 0xf0) | (color & 0xf));
}
void setBgColor(int bgcolor) {
	CONSOLE_SCREEN_BUFFER_INFO buff;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buff);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		((bgcolor & 0xf) << 4) | (buff.wAttributes & 0xf));
}
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
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
				printf("  ");
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
void titleDraw() {
	int x = 20; int y = 5; 
	gotoxy(x, y);
    printf("#      ##    ##   #####\n");
	gotoxy(x, y+1);
    printf("#     #  #  #  #    #  \n");
	gotoxy(x, y+2);
    printf("#     #  #  #  #    #  \n");
	gotoxy(x, y+3);
    printf("####   ##    ##     #  \n");
}
int maplist() {
	system("cls");
	int x = 24; int y = 12;
	int scale = 0;
	gotoxy(x - 2, y);
	printf("▣쉬움");
	gotoxy(x, y + 1);
	printf("보통");
	gotoxy(x, y + 2);
	printf("어려움");
	gotoxy(x, y + 3);
	printf("뒤로가기");
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
		case DOWN: if (y < 15) {
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
void drawUI(int *x, int*y) {
	setFontColor(WHITE);
	gotoxy(3, 16);
	printf("위치 : %02d,%02d", *x, *y);
	gotoxy(34, 16);
	printf("점수 추가예정");
}
void move(int* x, int* y, int playerx, int playery) {
	gotoxy(*x, *y);
	printf(" ");

	SetColor(VIOLET);
	gotoxy(*x + playerx, *y + playery);
	printf("★");

	*x += playerx;
	*y += playery;

}
int mapDraw(int i) {
	int player_x, player_y;
	int countx = 0, county = 0;
	char temp;
	system("cls");
	for (int j = 0; j < 73; j++) {
		countx++;
			switch (map[i][j])
			{
			case '0': printf("  ");
				break;
			case '1': SetColor(RED); printf("◎");
				break;
			case '2': SetColor(GREEN);  printf("▣");
				break;
			case '3': SetColor(DARK_VIOLET);  printf("▦");
				break;
			case '4': SetColor(VIOLET); printf("★");
				player_x = countx; player_y = county;
			break;
			case 'n': printf("\n");
				countx = 0; county ++;
				break;
			}
		}
	temp = map[i][player_x];
	for (;;) { // 게임 루프함수 
		drawUI(&player_x, &player_y);
		switch (keyControll())
		{
		case UP: if (temp == '3') continue;
				move(&player_x, &player_y, 0, -1);
			break;
			case DOWN: if (temp == '3') continue;
				move(&player_x, &player_y, 0, 1);
			break;
			case LEFT: if (temp == '3') continue;
				move(&player_x, &player_y, -1, 0);
			break;
			case RIGHT: if (temp == '3') continue;
				move(&player_x, &player_y, 1, 0);
			break;
			case ESC :
			system("cls");
			return 0;
		}
	}
}
int information() {
	
	system("cls");
	char info[4][45] = {
		{"조작법"},{"이동 : ←,↑,↓,→"},{"선택: 스페이스바"},{"스페이스바를 누르면 메인화면으로 이동합니다."}
	};
	
	for (int i = 0; i <4; i++) {
		for (int j = 0; j < 45; j++) {
			setFontColor(WHITE); printf("%c", info[i][j]);
		}
		printf("\n");
	}
	if (keyControll() == SUBMIT) {
		system("cls");
		return 0;
	}
}

int main() {
	int select;
	init();
	while (true)
	{
		titleDraw();
		int menu = menuDraw();
		system("cls");
		switch (menu)
		{
		case 0: 
			select = maplist();
			if (select == 0) mapDraw(0); 
		if (select == 1) mapDraw(1);
		if (select == 2) mapDraw(2);
		if (select == 3) {
			system("cls");
			break;
		}
		case 1: information();
			break;
		case 2:
			return 0;
		}
	}



	return 0;
}