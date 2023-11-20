// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int x, y, dir;

	

void drawTank(COLORREF c,int x,int y,int direction)
{
	setcolor(c);
	rectangle(-5 + x, -5 + y, 5 + x, 5 + y);
	rectangle(-15 + x, -15 + y, 15 + x, 15 + y);
	switch (dir)
	{
	case 0:
		line(0 + x, 0 + y, 0 + x, -25 + y);
		break;
	case 1:
		line(0 + x, 0 + y, 0 + x, 25 + y);
		break;
	case 2:
		line(0 + x, 0 + y, -25 + x, 0 + y);

	case 3:
		line(0 + x, 0 + y, 25 + x, 0 + y);
		break;
	default:
		break;
	}

}
void drawGame()
{
	setfillcolor(BLACK);
	fillrectangle(0,0,800,600);
	drawTank(YELLOW, x, y, dir);
	for (double i = 0; i < 20;i++)
	{
		drawTank(RGB(rand() % 256, rand() % 256, rand() % 256),120*cos(0.314*i)+x, 120 * sin(0.314 * i) + y, dir);
	}

}
void GameControl()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		dir = 0;
		y -= 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		dir = 0;
		y == 5;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		dir = 0;
		x -= 5;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		dir = 0;
		x -= 5;
	}
}
void GameLogic()
{

}

int main()
{
	x = 400; y = 300;
	initgraph(800, 600);
	BeginBatchDraw();
	while (1)
	{
		GameControl();
		drawGame();
		GameLogic();
		FlushBatchDraw();
		Sleep(100);
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
