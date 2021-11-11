#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#define Max_size 12
#define UP    72 // 키보드 방향키 코드 이값 
#define DOWN   80 // 한번만 받으면 일반 h 같은거 충돌함
#define LEFT   75 
#define RIGHT   77 
#define ESC 27 // 아스키 코드 ctrl + ecs == 27 
#define STAGE 3


void gotoxy(int x, int y) /*커서이동 함수 부분*/
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {
    char scale=0;
    int x = 0; int y = 0;
    while (true) {
        gotoxy(x, y);
        printf("▣");
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


