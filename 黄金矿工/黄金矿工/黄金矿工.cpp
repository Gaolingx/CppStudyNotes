// 黄金矿工.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <corecrt_math.h>

#define STATE_BAI 0
#define STATE_SHEN 1
#define STATE_LA 2
int state = STATE_BAI;
int lx = 400;
int ly = 250;
int lineLength = 150;
double d = 0;
double vd = 0.05;
int linespeed = -10;
struct Item
{
	int x;
	int y;
	int islife;
	int isdrag;
	int type;
	int r;
}ii[6] = {
	{40,450,1,0,2,30},
	{140,400,1,0,1,50},
	{380,480,1,0,0,30},
	{640,280,1,0,4,20},
	{740,380,1,0,3,30},
	{240,280,1,0,4,20},
};

IMAGE bk;
IMAGE i[5];
IMAGE ibw[5];

void loadRes()
{
	loadimage(&bk, L"黄金矿工背景.jpg", 800, 600);
	loadimage(&i[0], L"s10.png", 100, 100);
	loadimage(&ibw[0], L"s10a.png", 100, 100);
	loadimage(&i[1], L"s9.png", 60, 60);
	loadimage(&ibw[1], L"s9a.png", 60, 60);
	loadimage(&i[2], L"s15.png", 100, 100);
	loadimage(&ibw[2], L"s15a.png", 100, 100);
	loadimage(&i[3], L"s13.png", 60, 60);
	loadimage(&ibw[3], L"s14a.png", 60, 60);
	loadimage(&i[4], L"钻石.png", 40, 40);
	loadimage(&ibw[4], L"钻石a.png", 40, 40);
}
void drawGame()
{
	putimage(0, 100, &bk, SRCCOPY);
	setcolor(YELLOW);
	line(400, 100, lx, ly);
	for (int j = 0; j < 6; j++) 
	{
		if (ii[j].islife == 1) 
		{
			putimage(ii[j].x - ii[j].r, ii[j].y - ii[j].r, &i[ii[j].type], SRCINVERT);
			putimage(ii[j].x - ii[j].r, ii[j].y - ii[j].r, &ibw[ii[j].type], SRCAND);
			putimage(ii[j].x - ii[j].r, ii[j].y - ii[j].r, &i[ii[j].type], SRCINVERT);
		}
	}
}
int collide(Item i) 
{
	if (sqrt((lx - i.x) * (lx - i.x) + (ly - i.y) * (ly - i.y)) < i.r) {
		return 1;
	}
	else
		return 0;
}
void GameControl()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (state == STATE_BAI)
		{
			state = STATE_SHEN;
		}
	}
}
void GameLogic()
{
	lx = 400 + sin(d) * lineLength;
	ly = 100 + cos(d) * lineLength;
	switch (state)
	{
	case STATE_BAI:
		d += vd;
		if (d > 1.5 || d < -1.5)vd *= -1;

		break;
	case STATE_SHEN:
		lineLength += 5;
		for (int j = 0; j < 6; j++) {
			if (ii[j].islife == 1) {
				if (collide(ii[j])) {
					ii[j].isdrag = 1;
					linespeed = -1 * (10 - ii[j].r / 10);
					state = STATE_LA;
					break;
				}
			}
		}

		if (lineLength > 500) {
			state = STATE_LA;
		}
		break;
	case STATE_LA:

		lineLength += linespeed;
		for (int j = 0; j < 6; j++) {
			if (ii[j].islife == 1 && ii[j].isdrag == 1) {
				ii[j].x = lx;
				ii[j].y = ly;
				break;
			}
		}
		if (lineLength <= 100) {
			for (int j = 0; j < 6; j++) {
				if (ii[j].isdrag == 1) {
					ii[j].islife = 0;
					ii[j].isdrag = 0;
				}
			}
			state = STATE_BAI;
			lineLength = 150;
		}
		break;
	default:
		break;
	}
}

int main()
{
	initgraph(800, 600);
	BeginBatchDraw();
	loadRes();
	while (1)
	{
		drawGame();
		GameControl();
		GameLogic();
		FlushBatchDraw();
		Sleep(50);
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
