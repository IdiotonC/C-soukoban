#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#define Max_size 12
#define UP    72 // Ű���� ����Ű �ڵ� �̰� 
#define DOWN   80 // �ѹ��� ������ �Ϲ� h ������ �浹��
#define LEFT   75 
#define RIGHT   77 
#define ESC 27 // �ƽ�Ű �ڵ� ctrl + ecs == 27 
#define STAGE 3


void gotoxy(int x, int y) /*Ŀ���̵� �Լ� �κ�*/
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {
    char scale=0;
    int x = 0; int y = 0;
    while (true) {
        gotoxy(x, y);
        printf("��");
        if (_kbhit()) {
            scale = _getch();
            switch (scale)
            {
            case UP: y--;
                break;
            case DOWN: y++;
                break;
            case LEFT: x--;
                break;
            case RIGHT: x++;
                break;
            default: break;
            }
        }
        else if (scale == ESC) break;
        Sleep(50);
        system("cls");
    }
}


