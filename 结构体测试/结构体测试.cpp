// 结构体测试.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
struct Ball
{
	int x;
	int y;
	int vx, vy;
	int hp;
	int islife = 0;
	COLORREF color;
}
b[100];

int isgo = 1;

void createBall()
{
	for (int i = 0; i < 100; i++)
	{
		if (b[i].islife == 0)
		{
			b[i].islife = 1;
			b[i].x = 400;
			b[i].y = 300;
			b[i].vx = rand() % 21 - 10;
			b[i].vy = rand() % 21 - 10;
			b[i].hp = 5;
			b[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
			break;
		}
	}
}
void moveBall()
{
	int i;
	for (i = 0; i < 100; i++)
	{
		if (b[i].islife == 1)
		{
			b[i].x += b[i].vx;
			b[i].y += b[i].vy;

			if (b[i].x < 20 || b[i].x>780)
			{
			b[i].vx *= -1;
			b[i].hp--;
			}

			if (b[i].y < 20 || b[i].y>580)
			{
				b[i].vy *= -1;
				b[i].hp--;
			}
			if (b[i].hp <= 0)
			{
				b[i].islife = 0;
			}
			


		}

	}
}
void drawBall()
{
	int i;
	TCHAR c[10];
	for (i = 0; i < 100; i++)
	{
		setcolor(b[i].color);
		circle(b[i].x, b[i].y, 20);
		settextstyle(20, 0, L"宋体");
		wsprintf(c, L"%d", b[i].hp);
		outtextxy(b[i].x - 5, b[i].y - 10, c);
	}
}
void drawGame()
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 600);
	drawBall();
}
void GameControl()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && isgo==1) 
	{
		createBall();
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (isgo == 1)
			isgo = 0;
		else
			isgo = 1;
	}

}
void GameLogic()
{
	if (isgo == 1);
		moveBall();
}

int main()
{
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
