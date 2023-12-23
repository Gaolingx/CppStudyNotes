// ConsoleApplication7.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include "graphics.h"
#include <stdlib.h>
#include <time.h>
#include "mm.h"

IMAGE bk;
short(*map)[20];
int floor = 1;
int x = 1;
int y = 1;

void loadRes()
{
	loadimage(&bk, L"ditu1.bmp");
}

void Init()
{
	map = f1_map0;
}

void nextfloor(int floor) {
	switch (floor)
	{
	case 1:
		map[y][x] = 0;
		map = f1_map0;
		map[y][x] = 8;
		break;
	case 2:
		map[y][x] = 0;
		map = f2_map0;
		map[y][x] = 8;
		break;
	case 3:
		map[y][x] = 0;
		map = f3_map0;
		map[y][x] = 8;
		break;
	}
}

void drawGame()
{
	int i, j;
	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 640);
	for (i = 0; i < 20; i++)
		for (j = 0; j < 20; j++) {
			if (map[i][j] == 8) {
				setfillcolor(YELLOW);
				fillcircle(16 + j * 32, 16 + i * 32, 14);
			}
			else if (map[i][j] != 0) {
				putimage(0 + j * 32, 0 + i * 32, 32, 32, &bk,
					(map[i][j] - 1) % 6 * 32, (int)((map[i][j] - 1) / 6) * 32, SRCCOPY);
			}
		}
}

void GameControl()
{
		if (y > 0 && GetAsyncKeyState(VK_UP) & 0x8000) {
			if (map[y - 1][x] == 0) {
				map[y - 1][x] = 8;
				map[y][x] = 0;
				y--;
			}
			else if (map[y - 1][x] == 2) {
				floor++;
				nextfloor(floor);
			}
			else if (map[y - 1][x] == 34) {
				floor--;
				nextfloor(floor);
			}
		}

		if (y < 19 && GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (map[y + 1][x] == 0) {
				map[y + 1][x] = 8;
				map[y][x] = 0;
				y++;
			}
			else if (map[y + 1][x] == 2) {
				floor++;
				nextfloor(floor);
			}
			else if (map[y + 1][x] == 34) {
				floor--;
				nextfloor(floor);
			}
		}

		if (x > 0 && GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (map[y][x - 1] == 0) {
				map[y][x - 1] = 8;
				map[y][x] = 0;
				x--;
			}
			else if (map[y][x - 1] == 2) {
				floor++;
				nextfloor(floor);
			}
			else if (map[y][x - 1] == 34) {
				floor--;
				nextfloor(floor);
			}
		}
		if (x < 19 && GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (map[y][x + 1] == 0) {
				map[y][x + 1] = 8;
				map[y][x] = 0;
				x++;
			}
			else if (map[y][x + 1] == 2) {
				floor++;
				nextfloor(floor);
			}
			else if (map[y][x + 1] == 34) {
				floor--;
				nextfloor(floor);
			}
		}


	}

void GameLogic()
{

}

int main()
{
	initgraph(800, 600);
	BeginBatchDraw();
	loadRes();
	while (1)
	{
		Init();
		GameControl();
		drawGame();
		GameLogic();
		FlushBatchDraw();
		Sleep(60);
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
