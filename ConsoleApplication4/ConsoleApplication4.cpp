// ConsoleApplication4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>

struct pipe
{
	int x;
	int y;
	int width;
}p[10];

int bx = 400;
int by = 300;
int vy = 0;
int isdeath;

void initPipe()
{
	int i;
	for (i = 0; i < 10; i++)
	{
		p[i].x = 600 + i * 150;
		p[i].y = rand() % 150 + 100;
		p[i].width = rand() % 100 + 100;
	}
}
void drawGame()
{
	int i;
	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 600);
	for (i = 0; i < 10; i++)
	{
		setcolor(GREEN);
		setfillcolor(GREEN);
		fillrectangle(p[i].x, 0, p[i].x + 30, p[i].y);
		fillrectangle(p[i].x, p[i].y + p[i].width, p[i].x + 30, 600);

	}
	setcolor(RED);
	setfillcolor(RED);
	fillcircle(bx, by, 15);
}
void GameControl()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && isdeath == 0)
	{
		vy -= 5;
	}
}
void GameLogic()
{	
	int i;
	if (isdeath == 0)

	for (i = 0; i < 10; i++)
	{
		p[i].x -= 5;
		if (p[i].x <= -100)
		{
			p[i].x += 1500;
			p[i].y = rand() % 150 + 100;
			p[i].width = rand() % 100 + 100;
		}
		if (p[i].x > 355 && p[i].x < 415)
		{
			if (by - 15 < p[i].y || by + 15 > p[i].y + p[i].width)
			{
				isdeath = 1;
			}
		}
	}
	by += vy;
	vy += 1;
	if (by >= 600)exit(0);
}

int main()
{
	initgraph(800, 600);
	initPipe();
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
