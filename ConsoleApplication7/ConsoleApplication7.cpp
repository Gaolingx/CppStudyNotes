// ConsoleApplication7.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#define STATE_MENU 0
#define STATE_ABOUT 1
#define STATE_LOADING 2
#define STATE_GAME 3
void main()
{
	TCHAR c[3][100] = { L"启动！",L"关于游戏",L"退出游戏" };
	int i, state = STATE_MENU, flag = 0;
	int lx = 150;
	initgraph(800, 600);
	BeginBatchDraw();
	while (1)
	{
		setfillcolor(BLACK);
		fillrectangle(0, 0, 800, 600);
		switch (state)
		{
		case STATE_MENU:
			setcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
			settextstyle(55, 0, L"宋体");
			outtextxy(110, 100, L"奴 隶 少 女 希 尔 薇");
			settextstyle(20, 0, L"宋体");
			outtextxy(110, 200, L"冷狐无伤版 v1.0.11");
			settextstyle(32, 0, L"宋体");
			for (i = 0; i < 3; i++) {
				outtextxy(330, 250 + i * 80, c[i]);
			}
			setfillcolor(BLACK);
			fillrectangle(260, 255 + flag * 80, 290, 285 + flag * 80);
			break;

		case STATE_ABOUT:
			setcolor(WHITE);
			outtextxy(50, 50, L"这是一款日产单手FPS大作！");
			outtextxy(50, 150, L"由全民制作人制作");
			break;
		case STATE_GAME:
			setcolor(WHITE);
			settextstyle(55, 0, L"宋体");
			outtextxy(150, 100, L"预计114514天完成");
			break;
		}

		switch (state)
		{
		case STATE_MENU:
			if (GetAsyncKeyState(VK_UP) & 0x8000) {
				flag--;
				if (flag == -1)flag = 2;
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
				flag = (flag + 1) % 3;
			}
			if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
				if (flag == 0)state = STATE_LOADING;
				else if (flag == 1)state = STATE_ABOUT;
				else exit(0);
			}
			break;
		case STATE_ABOUT:
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
				state = STATE_MENU;
			}
			break;
		case STATE_LOADING:
			setcolor(WHITE);
			settextstyle(55, 0, L"宋体");
			outtextxy(110, 100, L"奴 隶 少 女 希 尔 薇");
			setcolor(WHITE);
			rectangle(150, 450, 650, 480);
			setcolor(WHITE);
			setfillcolor(WHITE);
			fillrectangle(151, 451, lx, 479);
			break;
		}

		switch (state)
		{
		case STATE_LOADING:
			lx += 5;
			if (lx >= 650) {
				state = STATE_GAME;
				lx = 150;
			}
			break;
		}
		Sleep(50);
		FlushBatchDraw();
	}
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
