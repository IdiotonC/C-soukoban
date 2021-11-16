#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#define UP    72 // Ű���� ����Ű �ڵ� �̰� 
#define DOWN   80 // �ѹ��� ������ �Ϲ� h ������ �浹��
#define LEFT   75 
#define RIGHT   77 
#define SUBMIT 32
#define ESC 27 // �ƽ�Ű �ڵ� ctrl + ecs == 27

using namespace std;

int x = 20; int y = 5; // ȭ�� �߾Ӱ� 

char map[8][8] = {
	{00222000},
	{00212000},
	{00202222},
	{22230312},
	{21030222},
	{22223200},
	{00021200},
	{00022200},
}; //����ü�� �Ϸ��� �ߴµ� �� �𸣰ھ �����س� ��

typedef struct map
{
	char map[3];
}gamemap; // ���Ӹ� �������ִ� ����ü 

int keyControll(void) {
	int scale = _getch();
	return scale;
} // Ű �Է°� �������� �� khbit ���� �;��µ� �� 

void gotoxy(int x, int y) /*Ŀ���̵� �Լ� �κ�*/
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void init() {
	system("mode con cols=56 lines=20");  // �ʱ�ȭ�� �ʱ�ȭ �Լ�
	
	HANDLE hConsole; // Ŀ�� ����� �ܼ�Ŀ�� ���� �Լ� 
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
	    printf("�ð��ӽ���");
	    gotoxy(x, y+1);
	    printf("���� ����");
	    gotoxy(x, y+2);
	    printf("����");
		while (true)
		{
			int menukey = keyControll();
			switch (menukey)
			{
			case UP: if (y > 12) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf("��");
			}
				   break;
			case DOWN: if (y < 14) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf("��");
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
		{"���۹�"},{"�̵� : ��,��,��,��"},{"����: �����̽���"},{"�����̽��ٸ� ������ ����ȭ������ �̵��մϴ�."}
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