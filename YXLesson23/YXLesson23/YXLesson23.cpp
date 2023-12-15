// YXLesson23.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <graphics.h>
#include "stdlib.h"
#include "math.h"
#define  STATE_BAI 0
#define  STATE_SHEN 1
#define  STATE_LA 2
#define  N 6
int lx = 400, ly = 200;
double d = 0;
double vd = 0.05;
int lineLength = 100;
int lineSpeed = -10;
int state = STATE_BAI;
TCHAR sc[20];
int money = 0;
struct Item
{
	int x;
	int y;
	int islife;
	int isdrag;
	int type;
	int r;
}ii[N] = { {100,500,1,0,0,50},
			{210,390,1,0,1,30},
			{320,450,1,0,2,50},
			{730,500,1,0,3,30},
			{500,360,1,0,4,20},
			{700,380,1,0,4,20} };

IMAGE bk;
IMAGE g[5];
IMAGE gbw[5];

int collide(Item i) {
	if (sqrt((lx - i.x)*(lx - i.x) + (ly - i.y)*(ly - i.y)) < i.r) {
		return 1;
	}
	else
	{
		return 0;
	}
}

void drawGame() {
	putimage(0, 100, &bk, SRCCOPY);
	setcolor(YELLOW);
	line(400, 100, lx, ly);
	for (int i = 0; i < N; i++) {
		if (ii[i].islife == 1) {
			putimage(ii[i].x - ii[i].r, ii[i].y - ii[i].r, &g[ii[i].type], SRCINVERT);
			putimage(ii[i].x - ii[i].r, ii[i].y - ii[i].r, &gbw[ii[i].type], SRCAND);
			putimage(ii[i].x - ii[i].r, ii[i].y - ii[i].r, &g[ii[i].type], SRCINVERT);
		}
	}
	settextstyle(50, 0, L"黑体");
	wsprintf(sc, L"金币：%d", money);
	outtextxy(50, 30, sc);
}
void ctrlGame() {
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (state == STATE_BAI)
			state = STATE_SHEN;
	}
}
void gameLogic() {
	lx = 400 + sin(d)*lineLength;
	ly = 100 + cos(d)*lineLength;
	switch (state)
	{
	case STATE_BAI:
		d += vd;
		if (d > 1.4 || d <= -1.4)vd *= -1;
		break;
	case STATE_SHEN:
		lineLength += 5;
		for (int i = 0; i < N; i++) {
			if (ii[i].islife == 1) {
				if (collide(ii[i])) {
					ii[i].isdrag = 1;
					state = STATE_LA;
					lineSpeed = -1 * (8 - ii[i].r / 10);
					break;
				}
			}
		}


		if (lineLength > 500) {
			state = STATE_LA;
		}
		break;
	case STATE_LA:
		lineLength += lineSpeed;
		for (int i = 0; i < N; i++) {
			if (ii[i].isdrag == 1) {
				ii[i].x = lx;
				ii[i].y = ly;
				break;
			}
		}
		if (lineLength <= 100) {
			for (int i = 0; i < N; i++) {
				if (ii[i].isdrag == 1) {
					ii[i].islife = 0;
					ii[i].isdrag = 0;
					switch (ii[i].type)
					{
					case 0:
						money += (500 + rand() % 200);
						break;
					case 1:
						money += (250 + rand() % 100);
						break;
					case 2:
						money += (100 + rand() % 80);
						break;
					case 3:
						money += (20 + rand() % 50);
						break;
					case 4:
						money += (850 + rand() % 150);
						break;
					default:
						break;
					}
					break;
				}

			}

			state = STATE_BAI;
			lineLength = 100;
			lineSpeed = -12;
		}
		break;
	default:
		break;
	}
}
int main()
{
	initgraph(800, 600);
	loadimage(&bk, L"黄金矿工背景.jpg", 800, 500);
	loadimage(&g[0], L"s10.png", 100, 100);
	loadimage(&gbw[0], L"s10a.png", 100, 100);
	loadimage(&g[1], L"s9.png", 60, 60);
	loadimage(&gbw[1], L"s9a.png", 60, 60);
	loadimage(&g[2], L"s15.png", 100, 100);
	loadimage(&gbw[2], L"s15a.png", 100, 100);
	loadimage(&g[3], L"s13.png", 60, 60);
	loadimage(&gbw[3], L"s14a.png", 60, 60);
	loadimage(&g[4], L"钻石.png", 40, 40);
	loadimage(&gbw[4], L"钻石a.png", 40, 40);
	BeginBatchDraw();
	while (1)
	{
		drawGame();
		ctrlGame();
		gameLogic();
		FlushBatchDraw();
		Sleep(30);
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
