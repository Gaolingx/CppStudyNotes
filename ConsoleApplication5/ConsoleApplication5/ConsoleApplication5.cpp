// ConsoleApplication5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PLAYER_1 0
#define PLAYER_2 1

int isgo = 0;//发射
IMAGE ip1, ip2;//人物
TCHAR c[20];
MOUSEMSG mm;//鼠标控制
double lineLength;//长度
double d;//角度
int gametime = 0;
int mx = 0;//滚动

struct player
{
	int x;
	int hp = 100;
	TCHAR name[10];
}p1, p2;
struct ball
{
	int x;
	int y;
	int vx;
	int vy;
}b;
int player = PLAYER_1;
int x1, x2, g1, y2;

void Init()
{
	p1.x = 0;
	p2.x = 800 + rand() % 300;
	wsprintf(p1.name, L"哈基米");
	wsprintf(p2.name, L"单身狗");
	b.x = 40;
	b.y = 500;//猫的子弹高度
}

void loadRes()
{
	loadimage(&ip1, L"猫.jpg", 80, 80);
	loadimage(&ip2, L"狗.jpg", 80, 80);

}

void drawGame()
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 600);
	putimage(p1.x - mx, 520, &ip1, SRCCOPY);
	putimage(p2.x - mx, 520, &ip2, SRCCOPY);
	outtextxy(p1.x - mx, 450, p1.name);
	wsprintf(c, L"生命:%d", p1.hp);
	outtextxy(p1.x + 60 - mx, 450, c);
	outtextxy(p2.x - mx - 60, 450, p2.name);
	wsprintf(c, L"生命:%d", p2.hp);
	outtextxy(p2.x - mx - 10, 450, c);
	setfillcolor(YELLOW);//画一个圆
	fillcircle(b.x, b.y, 20);
	if (player == PLAYER_1)
		setcolor(CYAN);
	else 
		setcolor(GREEN);
	line(x1, g1, x2, y2);
}

void GameControl()
{
	if (MouseHit() && isgo == 0)
	{
		mm = GetMouseMsg();
		switch (mm.uMsg)
		{
		case WM_LBUTTONDOWN:

			x1 = mm.x;
			g1 = mm.y;
			x2 = mm.x;
			y2 = mm.y;
			break;
		case WM_MOUSEMOVE:
			if (x1 > 0)
			{
				x2 = mm.x;
				y2 = mm.y;
			}
			break;
		case WM_LBUTTONUP:
			x2 = mm.x;
			y2 = mm.y;
			isgo = 1;
			lineLength = sqrt((x1 - x2) * (x1 - x2) + (g1 - y2) * (g1 - y2));
			d = atan2((g1 - y2), (x1 - x2));
			b.vx = cos(d) * lineLength * 0.1;
			b.vy = sin(d) * lineLength * 0.1;
			if (b.vy > 0)
			{
				b.vy *= -1;
				b.vx *= -1;
			}
			break;
		}
	}
}

void GameLogic()
{
	if (isgo == 1)
	{
		gametime++;
		if (gametime % 5 == 0)
		{
			if (player == PLAYER_1)
			{
				if (b.x < 400)
					b.x += b.vx;
				else
					mx += b.vx;
			}
			if (player == PLAYER_2)
			{
				if (b.x > 400)
					b.x += b.vx;
				else
					mx += b.vx;
			}
			b.y += b.vy;
			b.vy += 1;
			if (player == PLAYER_1)
			{
				if (sqrt((b.x - p2.x + mx - 40) * (b.x - p2.x + mx - 40) + (b.y - 560) * (b.y - 560)) < 100)
				{
					b.y = 620;
					p2.hp -= 20;
				}
			}
			if (player == PLAYER_2)
			{
				if (sqrt((b.x - p1.x + mx - 40) * (b.x - p1.x + mx - 40) + (b.y - 560) * (b.y - 560)) < 100)
				{
					b.y = 620;
					p1.hp -= 20;
				}
			}
			if (b.y > 600)
			{
				if (player == PLAYER_1)
				{
					player = PLAYER_2; b.x = 760; mx = p2.x - 720;
				}
				else
				{
					player = PLAYER_1; b.x = 40; mx = 0;
				}
				b.y = 500;
				isgo = 0;
				x1 = -1;
				g1 = -1;
				x2 = -1;
				y2 = -1;
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	initgraph(800, 600);
	BeginBatchDraw();
	loadRes();
	Init();
	while (1)
	{
		GameControl();
		drawGame();
		GameLogic();
		Sleep(10);
		FlushBatchDraw();
		
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
