// 海里捞金.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <graphics.h>
#include "stdlib.h"
#include "math.h"

#define STATE_MENU 10
#define STATE_ABOUT 11
#define STATE_LOADING 12
#define STATE_GAME 13
#define  STATE_BAI 0
#define  STATE_SHEN 1
#define  STATE_LA 2
#define  N 6

TCHAR uic[3][100] = { L"启动！",L"关于游戏",L"退出游戏" };
int uii, uistate = STATE_GAME, uiflag = 0;
int uilx = 150;

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
IMAGE player;
IMAGE player_a;
IMAGE g[5];
IMAGE gbw[5];

void loadRes()
{
	loadimage(&bk, L"量子之海background.jpg", 800, 500);
	loadimage(&player, L"Tex_player_希儿_rgba.png", 100, 100);
	loadimage(&player_a, L"Tex_player_希儿_a.png", 100, 100);
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
}

int collide(Item i) {
	if (sqrt((lx - i.x) * (lx - i.x) + (ly - i.y) * (ly - i.y)) < i.r) {
		return 1;
	}
	else
	{
		return 0;
	}
}

void drawGame() {
	if (STATE_GAME)
	{
		//绘制背景
		putimage(0, 100, &bk, SRCCOPY);

		//绘制玩家
		putimage(350, 0, &player, SRCCOPY);

		//绘制钩子
		setcolor(YELLOW);
		line(400, 100, lx, ly);
		//TODO 加上钩子图片

		//绘制宝石
		for (int i = 0; i < N; i++) {
			if (ii[i].islife == 1) {
				putimage(ii[i].x - ii[i].r, ii[i].y - ii[i].r, &g[ii[i].type], SRCINVERT);
				putimage(ii[i].x - ii[i].r, ii[i].y - ii[i].r, &gbw[ii[i].type], SRCAND);
				putimage(ii[i].x - ii[i].r, ii[i].y - ii[i].r, &g[ii[i].type], SRCINVERT);
			}
		}

		//绘制UI
		settextstyle(50, 0, L"黑体");
		wsprintf(sc, L"金币：%d", money);
		outtextxy(50, 30, sc);
	}
}
void ctrlGame() {
	if (STATE_MENU || STATE_ABOUT)
	{
		//UI控制
		switch (uistate)
		{
		case STATE_MENU:
			if (GetAsyncKeyState(VK_UP) & 0x8000) {
				uiflag--;
				if (uiflag == -1)
				{
					uiflag = 2;
				}
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
				uiflag = (uiflag + 1) % 3;
			}
			if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
				if (uiflag == 0)uistate = STATE_LOADING;
				else if (uiflag == 1)uistate = STATE_ABOUT;
				else exit(0);
			}
			break;
		case STATE_ABOUT:
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
				uistate = STATE_MENU;
			}
			break;
		case STATE_LOADING:
			setcolor(WHITE);
			settextstyle(55, 0, L"宋体");
			outtextxy(110, 100, L"原 来 你 也 玩 原 神");
			setcolor(WHITE);
			rectangle(150, 450, 650, 480);
			setcolor(WHITE);
			setfillcolor(WHITE);
			fillrectangle(151, 451, uilx, 479);
			break;
		}
	}
	//游戏控制
	if (STATE_GAME)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (state == STATE_BAI)
				state = STATE_SHEN;
		}
	}

}
void scoreCalculate(int Money, int randNum, bool addMoney)
{
	if (addMoney == true)
	{
		money += (Money + rand() % randNum);
	}
	else
	{
		money -= Money;
	}
}
void gameLogic() {
	if (STATE_GAME)
	{
		lx = 400 + sin(d) * lineLength;
		ly = 100 + cos(d) * lineLength;
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
							scoreCalculate(500, 200, true);
							//money += (500 + rand() % 200);
							break;
						case 1:
							scoreCalculate(250, 100, true);
							//money += (250 + rand() % 100);
							break;
						case 2:
							scoreCalculate(100, 80, true);
							//money += (100 + rand() % 80);
							break;
						case 3:
							scoreCalculate(20, 50, true);
							//money += (20 + rand() % 50);
							break;
						case 4:
							scoreCalculate(850, 150, true);
							//money += (850 + rand() % 150);
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
}
void drawGameUI()
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 600);

	switch (uistate)
	{
	case STATE_MENU:
		setcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		settextstyle(55, 0, L"宋体");
		outtextxy(110, 100, L"海 里 捞 金 极 速 版");
		setcolor(GREEN);
		settextstyle(20, 0, L"宋体");
		outtextxy(110, 200, L"冷狐无伤版 v1.0.11");
		settextstyle(32, 0, L"宋体");
		for (uii = 0; uii < 3; uii++) {
			outtextxy(330, 250 + uii * 80, uic[uii]);
		}
		setfillcolor(BLACK);
		fillrectangle(260, 255 + uiflag * 80, 290, 285 + uiflag * 80);
		break;

	case STATE_ABOUT:
		setcolor(WHITE);
		settextstyle(25, 0, L"宋体");
		outtextxy(50, 50, L"你说的对，但是《海里捞金》是由高羚翔自主研发的一款全新开放");
		outtextxy(50, 75, L"世界寻宝游戏。游戏发生在一个被称作「量子之海」的幻想世界，");
		outtextxy(50, 100, L"你将扮演一位名为「矿工」的神秘角色，收集神秘之物。");
		settextstyle(15, 0, L"宋体");
		outtextxy(300, 450, L"由软件游戏3231班高羚翔制作，版权所有2024 , 保留所有权利。");
		break;
	case STATE_GAME:
		setcolor(WHITE);
		settextstyle(55, 0, L"宋体");
		drawGame();
		break;
	}

	switch (uistate)
	{
	case STATE_LOADING:
		uilx += 5;
		if (uilx >= 650) {
			uistate = STATE_GAME;
			uilx = 150;
		}
		break;
	}
}
int main()
{
	initgraph(800, 600);
	loadRes();
	BeginBatchDraw();
	while (1)
	{
		drawGameUI();
		ctrlGame();
		gameLogic();
		FlushBatchDraw();
		Sleep(50);
	}
	EndBatchDraw();
	closegraph();

	return 0;
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
