// ConsoleApplication9.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "graphics.h"
#include <time.h>
#include "windows.h"
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")

struct floor
{
	int id;
	COLORREF b[8];

}f[20];

void initFloor()
{
	int temp;
	for (int i = 0; i < 20; i++)
	{
		f[i].id = i;
		temp = rand() % 8;
		for (int j = 0; j < 8; j++)
		{
			if (j == temp)
			{
				f[i].b[j] = BLACK;
			}
			else
			{
				f[i].b[j] = WHITE;
			}
		}

	}
}

void dropFloor()
{
	for (int i = 0; i < 20; i++)
	{
		if (f[i].id == 0)
		{
			f[i].id = 20;
			int temp = rand() % 8;
			for (int j = 0; j < 8; j++)
			{
				if (j == temp)
				{
					f[i].b[j] = BLACK;
				}
				else
				{
					f[i].b[j] = WHITE;
				}
				break;
			}
		}
		
	}
	for (int i = 0; i < 20; i++)
	{
		f[i].id--;
	}

}

void loadRes()
{

}

void Init()
{
	initgraph(480, 800);
	//set Timer
	srand(time(NULL));
}

void playSound()
{
	PlaySound(L"bgm.wav", NULL, SND_FILENAME || SND_ASYNC || SND_LOOP);
}

void drawGame()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			setcolor(BLACK);
			setfillcolor(f[i].b[j]);
			fillrectangle(0 + j * 60, 700 - f[i].id * 100, 60 + j * 60, 800 - f[i].id * 100);

		}
	}
}

void GameControl()
{
	MOUSEMSG mm;
	if (MouseHit())
	{
		mm = GetMouseMsg();
		if (mm.uMsg == WM_LBUTTONDOWN && mm.y > 700)
		{
			int col = mm.x / 60;
			for (int i = 0; i < 20; i++)
			{
				if (f[i].id == 0)
				{
					if (f[i].b[col] == BLACK)
					{
						dropFloor();
					}
					else
					{
						f[i].b[col] = RED;
					}
					break;

				}
			}
		}
	}
}

void GameLogic()
{

}

int main()
{
	Init();
	playSound();
	initFloor();
	BeginBatchDraw();

	while (1)
	{
		GameControl();
		drawGame();
		GameLogic();
		FlushBatchDraw();
		//Sleep(100);
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
