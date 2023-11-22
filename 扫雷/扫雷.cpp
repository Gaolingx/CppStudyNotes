// 扫雷.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "stdio.h"
#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>

TCHAR c[10];
COLORREF cc[9] = { WHITE,GREEN,BLUE,RED,YELLOW,BROWN,CYAN ,MAGENTA ,RGB(200,200,200) };
static int array[30][30];
int cx = 14, cy = 14;
int isdeath = 0;

void initArray()
{
	int i, j;
	for (i = 0; i < 30; i++)
	{
		for (j = 0; j < 30; j++)
		{
			array[i][j] = 0;
		}
		

	}
}

void createBomb(int n)
{
	for (int i = 0; i < n;)
	{
		int row = rand() % 30;
		int col = rand() % 30;
		if (array[row][col] == 0)
		{
			array[row][col] = 9;
			i++;
		}
	}
}

void fillArray()
{
	int i, j, count;
	for (i = 0; i < 30; i++)
	{
		for (j = 0; j < 30; j++)
		{

			if (array[i][j] == 0)
			{
				count = 0;
				if (i > 0 && array[i - 1][j] == 9)
					count++;
				if (i < 29 && array[i + 1][j] == 9)
					count++;
				if (i > 0 && array[i][j - 1] == 9)
					count++;
				if (i < 29 && array[i][j + 1] == 9)
					count++;

				if (i > 0 && j > 0 && array[i - 1][j - 1] == 9)
					count++;
				if (i < 29 && j < 29 && array[i - 1][j] == 9)
					count++;
				if (i > 0 && i < 29 && array[i + 1][j - 1] == 9)
					count++;
				if (i < 29 && i > 0 && array[i - 1][j + 1] == 9)
					count++;
				array[i][j] = count;

			}
		}
	}
}
void testshowArray()
{
	int i, j;
	for (i = 0; i < 30; i++)
	{
		for (j = 0; j < 30; j++)
		{
			array[i][j] += 10;
		}
	}
}
void drawGame()
{
	int i, j;
	setfillcolor(BLACK);
	fillrectangle(0, 0, 600, 800);
	for (i = 0; i < 30; i++)
		for (j = 0; j < 30; j++) {
			if (array[i][j] <= 9) {
				setcolor(WHITE);
				rectangle(0 + j * 20, 200 + i * 20, 20 + j * 20, 220 + i * 20);
			}
			else if (array[i][j] < 19) {
				setcolor(cc[array[i][j] - 10]);
				rectangle(0 + j * 20, 200 + i * 20, 20 + j * 20, 220 + i * 20);
				wsprintf(c, L"%d", array[i][j] - 10);
				outtextxy(5 + j * 20, 202 + i * 20, c);
			}
			else if (array[i][j] == 19) {
				setcolor(RED);
				rectangle(0 + j * 20, 200 + i * 20, 20 + j * 20, 220 + i * 20);
				setfillcolor(RED);
				fillcircle(10 + j * 20, 210 + i * 20, 8);
			}
		}
	setcolor(RGB(150, 0, 150));
	setfillcolor(RGB(150, 0, 150));
	fillcircle(10 + cx * 20, 210 + cy * 20, 5);
}

void isNum(int cx, int cy)
{
	array[cy][cx] += 10;
}

void isBomb()
{
	int i, j;
	for (i = 0; i < 30; i++)
	{
	for (j = 0; j < 30; j++)
	{
		if (array[i][j] == 9)array[i][j] += 10;
	}
	}

}

void isNull(int cx, int cy) {
	array[cy][cx] += 10;
	if (cy > 0 && array[cy - 1][cx] < 9) {
		if (array[cy - 1][cx] != 0)isNum(cx, cy - 1);
		else isNull(cx, cy - 1);
	}
	if (cy < 29 && array[cy + 1][cx] < 9) {
		if (array[cy + 1][cx] != 0)isNum(cx, cy + 1);
		else isNull(cx, cy + 1);
	}
	if (cx > 0 && array[cy][cx - 1] < 9) {
		if (array[cy][cx - 1] != 0)isNum(cx - 1, cy);
		else isNull(cx - 1, cy);
	}
	if (cx < 29 && array[cy][cx + 1] < 9) {
		if (array[cy][cx + 1] != 0)isNum(cx + 1, cy);
		else isNull(cx + 1, cy);
	}

	if (cy > 0 && cx > 0 && array[cy - 1][cx - 1] < 9) {
		if (array[cy - 1][cx - 1] != 0)isNum(cx - 1, cy - 1);
		else isNull(cx - 1, cy - 1);
	}
	if (cy < 29 && cx < 29 && array[cy + 1][cx + 1] < 9) {
		if (array[cy + 1][cx + 1] != 0)isNum(cx + 1, cy + 1);
		else isNull(cx + 1, cy + 1);
	}
	if (cx > 0 && cy < 29 && array[cy + 1][cx - 1] < 9) {
		if (array[cy + 1][cx - 1] != 0)isNum(cx - 1, cy + 1);
		else isNull(cx - 1, cy + 1);
	}
	if (cx < 29 && cy>0 && array[cy - 1][cx + 1] < 9) {
		if (array[cy - 1][cx + 1] != 0)isNum(cx + 1, cy - 1);
		else isNull(cx + 1, cy - 1);
	}

}
void GameControl()
{
	if (isdeath == 0)
	{


		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			cy--;
			if (cy < 0)cy = 29;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			cy = (cy + 1) % 30;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			cx--;
			if (cx < 0)cx = 29;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			cx = (cx + 1) % 30;
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			if (array[cy][cx] < 10) {
				if (array[cy][cx] < 9 && array[cy][cx]>0)isNum(cx, cy);
				else if
					(array[cy][cx] == 9)isBomb(), isdeath = 1;

				else if
					(array[cy][cx] == 0)isNull(cx, cy);
			}
		}
	}
		else
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				initArray();
				createBomb(90);
				fillArray();
				cx = 14;
				cy = 14;
				isdeath = 0;
			}
		}
	
}


void GameLogic()
{

}

int main()
{
	initgraph(600, 800);
	srand(time(NULL));
	initArray();
	createBomb(99);
	fillArray();
	//testshowArray();
	BeginBatchDraw();
	while (1)
	{
		GameControl();
		drawGame();
		GameLogic();
		FlushBatchDraw();
		Sleep(100);
	}
	EndBatchDraw();
	closegraph();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
