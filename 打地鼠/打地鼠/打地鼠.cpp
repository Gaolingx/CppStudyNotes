// 打地鼠.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>

IMAGE bk;
IMAGE hm, hmbw;
IMAGE ms, msbw;
int hx = 400, hy = 300;
int frame = 0;
int isPush = 0;
int countmouse = 0;
int gametime = 0;
int src = 0;
TCHAR sc[20];

struct mouse
{
	int x;
	int y;
	int time;
	int islife = 0;
	int frame = 4;
}m[9];

void createMouse()
{
	if (countmouse < 9)
	{
		while (1)
		{
			int w = rand() % 9;
			if (m[w].islife == 0)
			{
				m[w].islife =1;
				m[w].x = w % 3;
				m[w].y = w / 3;
				m[w].time = 0;
				m[w].frame = 4;
				countmouse++;
				break;
			}
		}
	}
}
void drawMouse()
{
	for (int i = 0; i < 9; i++)
	{
		if (m[i].islife == 1)
		{
			putimage(132 + 224 * m[i].x, 90 + 170 * m[i].y, 80, 80, &ms, 0 + 80 * m[i].frame, 0, SRCINVERT);
			putimage(132 + 224 * m[i].x, 90 + 170 * m[i].y, 80, 80, &msbw, 0 + 80 * m[i].frame, 0, SRCAND);
			putimage(132 + 224 * m[i].x, 90 + 170 * m[i].y, 80, 80, &ms, 0 + 80 * m[i].frame, 0, SRCINVERT);

		}
	}
}
void drawHummer(int x, int y, int frame)
{
	putimage(x, y, 50, 50, &hm, frame * 50, 0, SRCINVERT);
	putimage(x, y, 50, 50, &hmbw, frame * 50, 0, SRCAND);
	putimage(x, y, 50, 50, &hm, frame * 50, 0, SRCINVERT);
}

void drawGame()
{
	putimage(0, 0, &bk, SRCCOPY);
	drawHummer(hx, hy, frame);
	drawMouse();
	settextstyle(40, 0, L"黑体");
	wsprintf(sc, L"得分：%d", src);
	outtextxy(50, 50, sc);

}
void GameControl()
{
	if (MouseHit())
	{
		MOUSEMSG mm = GetMouseMsg();
		switch (mm.uMsg)
		{
		case WM_LBUTTONDOWN:
			int row, col;
			if (mm.x > 132 && mm.y > 90)
			{
				col = (mm.x - 132) / 224;
				row = (mm.y - 90) / 170;
				if (m[row * 3 + col].islife == 1)
				{
					m[row * 3 + col].islife = 0;
					countmouse--;
					src += (1 + m[row * 3 + col].frame * 2);
				}
			}
			isPush = 1;
			break;
		case WM_LBUTTONUP:
			isPush = 0;
			frame = 0;
		case WM_MOUSEWHEEL:
			break;
		case WM_MOUSEMOVE:
			hx = mm.x - 25;
			hy = mm.y - 25;
			break;
		default:
			break;
		}
	}
}

void moveMouse()
{
	for (int i = 0; i < 9; i++)
	{
		if (m[i].islife == 1)
		{
			m[i].time++;
			m[i].frame = 4 - m[i].time / 250;
			if (m[i].frame < 0)
			{
				m[i].islife = 0;
				countmouse--;
				src -= 5;
			}
		}
	}
}
void GameLogic()
{
	if (isPush == 1)
		frame = (frame + 1) % 3;

	gametime++;
	if (gametime % 1000 == 0)
	{
		createMouse();
	}
	moveMouse();
}

int main()
{
	initgraph(800, 600);
	loadimage(&bk, L"111.png", 800, 600);
	loadimage(&hm, L"chuizi.png", 150, 50);
	loadimage(&hmbw, L"chuizia.png", 150, 50);
	loadimage(&ms, L"laoshu.png", 400, 80);
	loadimage(&msbw, L"laoshua.png", 400, 80);
	BeginBatchDraw();
	while (1)
	{
		drawGame();
		GameControl();
		GameLogic();
		FlushBatchDraw();
		Sleep(5);
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
