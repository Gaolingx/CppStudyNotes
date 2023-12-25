// ConsoleApplication8.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include "graphics.h"
#include <stdlib.h>
#include <time.h>
#include "dt.h"

IMAGE bk;
IMAGE zj, zjhb;
int *frameArray;
int endframe = 3;
int frame = 0;
static int lstand[11] = { 10,9,8 };
static int rstand[11] = { 11,12,13 };
static int lrun[11] = { 32,31,30,29,28,27,26,25 };
static int rrun[11] = { 33,34,35,36,37,38,39,40 };
int lattack[11] = { 186,185,184,183,182,181,180,179,178,177,176 };
int rattack[11] = { 187,188,189,190,191,192,193,194,195,196,197 };

int zx = 50, zy = 500;
int zdirection = 0;  //0表示左

void drawMap(IMAGE bk, int maxRow, int maxCol)
{
	int i, j;
	for (i = 0; i < maxRow; i++)
		for (j = 0; j < maxCol; j++)
		{
			putimage(0 + j * 16, 0 + i * 16, 16, 16, &bk,
				(map0[i][j] - 1) % 12 * 16, (map0[i][j] - 1) / 12 * 16, SRCCOPY);
		}
}
void loadRes()
{
	loadimage(&bk, L"ditu1.bmp");
	loadimage(&zj, L"rwqh.png", 1408, 768);
	loadimage(&zjhb, L"rwqhhb.png", 1408, 768);
}

void Init()
{
	frameArray = rstand;
	endframe = 3;

}

void drawGame()
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 640);
	drawMap(bk, 40, 200);

	putimage(zx, zy, 64, 64, &zj,
		0 + frameArray[frame] % 22 * 64, 0 + frameArray[frame] / 22 * 64, SRCINVERT);
	putimage(zx, zy, 64, 64, &zjhb,
		0 + frameArray[frame] % 22 * 64, 0 + frameArray[frame] / 22 * 64, SRCAND);
	putimage(zx, zy, 64, 64, &zj,
		0 + frameArray[frame] % 22 * 64, 0 + frameArray[frame] / 22 * 64, SRCINVERT);
}

void GameControl()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		zdirection = 1;
		frameArray = lrun;
		endframe = 8;
		zx -= 8;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		zdirection = 0;
		frameArray = rrun;
		endframe = 8;
		zx += 8;
	}
}

void GameLogic()
{
	int row, col;
	frame = (frame + 1) % endframe;
	zy += 5;
	row = (zy + 64) / 16;
	col = (zx + 32) / 16;
	if (map0[row][col] != 0)
	{
		zy -= 5;
		if (zdirection == 0)
		{
			frameArray = rstand;
			endframe = 3;
		}
		else
		{
			frameArray = lstand;
			endframe = 3;
		}
	}
}

int main()
{
	initgraph(800, 640);
	BeginBatchDraw();
	loadRes();
	Init();
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
