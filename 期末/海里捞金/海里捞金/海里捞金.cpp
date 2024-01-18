﻿// 海里捞金.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <graphics.h>
#include "stdlib.h"
#include "math.h"
#include "windows.h"
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")

#define STATE_UI_MENU 10
#define STATE_UI_ABOUT 11
#define STATE_UI_LOADING 12
#define STATE_UI_GAME 13
#define STATE_UI_WIN 14
#define  STATE_BAI 0
#define  STATE_SHEN 1
#define  STATE_LA 2
#define  N 6

int gameLevel;
TCHAR uic[3][100] = { L"启动！",L"关于游戏",L"退出游戏" };
//int uistate = STATE_UI_WIN;
int uistate = STATE_UI_MENU;
int uii, uiflag = 0;
int uilx = 150;

int lx = 400, ly = 200;
double d = 0;
double vd = 0.05;
int lineLength = 100;
int lineSpeed = -10;
int state = STATE_BAI;
TCHAR sc[20];
TCHAR level[20];
int money = 0;

struct Item
{
	int x;
	int y;
	int islife;
	int isdrag;
	int type;
	int r;
	int has_life; // 用于标记是否有islife等于1的元素
}ii[N] = { {100,500,1,0,0,50},
			{210,390,1,0,1,30},
			{320,450,1,0,2,50},
			{730,500,1,0,3,30},
			{500,360,1,0,4,20},
			{700,380,1,0,4,20} };

IMAGE bg;
IMAGE bk;
IMAGE player;
IMAGE player_a;
IMAGE hook;
IMAGE hook_a;
IMAGE g[5];
IMAGE gbw[5];

void loadRes()
{
	loadimage(&bg, L"黄金矿工背景.jpg", 800, 600);
	loadimage(&bk, L"量子之海background.jpg", 800, 500);
	loadimage(&player, L"Tex_player_希儿_rgba.png", 100, 100);
	loadimage(&player_a, L"Tex_player_希儿_a.png", 100, 100);
	loadimage(&hook, L"钩子(hook)_rgba.png", 28.7, 50);
	loadimage(&hook_a, L"钩子(hook)_a.png", 28.7, 50);
	loadimage(&g[0], L"水晶_rgb.png", 60, 60);
	loadimage(&gbw[0], L"水晶_a.png", 60, 60);
	loadimage(&g[1], L"星石_rgb.png", 60, 60);
	loadimage(&gbw[1], L"星石_a.png", 60, 60);
	loadimage(&g[2], L"金币s_rgb.png", 80, 80);
	loadimage(&gbw[2], L"金币s_a.png", 80, 80);
	loadimage(&g[3], L"金币_rgb.png", 60, 60);
	loadimage(&gbw[3], L"金币_a.png", 60, 60);
	loadimage(&g[4], L"水晶s_rgb.png", 40, 40);
	loadimage(&gbw[4], L"水晶s_a.png", 40, 40);
}

void playBGSound(const LPCWSTR fileName)
{
	PlaySound(fileName, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void playHookSound(const LPCWSTR fileName)
{
	PlaySound(fileName, NULL, SND_FILENAME | SND_ASYNC);
}

void playAddCoinSound(const LPCWSTR fileName)
{
	PlaySound(fileName, NULL, SND_FILENAME | SND_ASYNC);
}

void playWinSound(const LPCWSTR fileName)
{
	PlaySound(fileName, NULL, SND_FILENAME | SND_ASYNC);
}

void levelSelect()
{
	//选择难度
	printf("请选择难度级别（输入数字1-5然后Enter确定）\n");
	scanf_s("%d", &gameLevel);
}

void drawCoin()
{
	for (int i = 0; i < N; i++) {
		if (ii[i].islife == 1) {
			putimage(ii[i].x - ii[i].r, ii[i].y - ii[i].r, &g[ii[i].type], SRCINVERT);
			putimage(ii[i].x - ii[i].r, ii[i].y - ii[i].r, &gbw[ii[i].type], SRCAND);
			putimage(ii[i].x - ii[i].r, ii[i].y - ii[i].r, &g[ii[i].type], SRCINVERT);
		}
	}
}
void GameInit()
{

	for (int i = 0; i < N; i++) //将数组中所有元素的islife重置为1，否则无法重新绘制金币
	{
		ii[1].x = 100;
		ii[2].x = 210;
		ii[3].x = 320;
		ii[4].x = 730;
		ii[5].x = 500;
		ii[6].x = 700;
		ii[1].y = 500;
		ii[2].y = 390;
		ii[3].y = 450;
		ii[4].y = 500;
		ii[5].y = 360;
		ii[6].y = 380;

		ii[i].has_life = 0;
		ii[i].islife = 1;

	}

	drawCoin(); //重新绘制所有金币

	money = 0; //重试游戏会清空当前money
	gameLevel = gameLevel + 1; //重试之后难度会增加
	uistate = STATE_UI_GAME;
	state = STATE_BAI;

}
void drawGameBG(int UbgDstX, int UbgDstY)
{
	putimage(UbgDstX, UbgDstY, &bk, SRCCOPY);
}
void drawUIBG(int GbgDstX, int GbgDstY)
{
	putimage(GbgDstX, GbgDstY, &bg, SRCCOPY);
}

void drawPlayer(int playerDstX, int playerDstY)
{
	putimage(playerDstX, playerDstY, &player, SRCINVERT);
	putimage(playerDstX, playerDstY, &player_a, SRCAND);
	putimage(playerDstX, playerDstY, &player, SRCINVERT);
}

void drawLine(COLORREF lineColor, int lineInitX, int lineInitY, int lineDstX, int lineDstY)
{
	setcolor(lineColor);
	line(lineInitX, lineInitY, lineDstX, lineDstY);
}

void drawHook(int hookDstX, int hookDstY)
{
	putimage(hookDstX, hookDstY, &hook, SRCINVERT);
	putimage(hookDstX, hookDstY, &hook_a, SRCAND);
	putimage(hookDstX, hookDstY, &hook, SRCINVERT);
}

void drawHUD()
{
	settextstyle(50, 0, L"黑体");
	wsprintf(sc, L"金币：%d", money);
	outtextxy(50, 30, sc);

	settextstyle(50, 0, L"黑体");
	wsprintf(level, L"难度：%d", gameLevel);
	outtextxy(550, 30, level);

}
void drawGame() {
	if (uistate == STATE_UI_GAME)
	{
		//绘制背景
		drawGameBG(0, 100);

		//绘制玩家
		drawPlayer(350, 0);

		//绘制绳子
		drawLine(YELLOW, 400, 100, lx, ly);

		//绘制宝石
		drawCoin();

		//绘制HUD
		drawHUD();
	}
}

void ExitGame()
{

	EndBatchDraw();
	closegraph();

	exit(0);
}

void ctrlGame()
{
	//UI控制
	switch (uistate)
	{
	case STATE_UI_MENU:
		if (uistate == STATE_UI_MENU)
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000) {
				uiflag--;
				if (uiflag == -1)
				{
					uiflag = 2;
				}
				Sleep(50);
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
				uiflag = (uiflag + 1) % 3;
				Sleep(50);
			}
			if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
				if (uiflag == 0)
				{
					uistate = STATE_UI_LOADING;
				}
				else if (uiflag == 1)
				{
					uistate = STATE_UI_ABOUT;
				}
				else
				{
					ExitGame();
				}
				Sleep(50);
			}
		}
		break;
	case STATE_UI_ABOUT:
		if (uistate == STATE_UI_ABOUT)
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
				uistate = STATE_UI_MENU;
				Sleep(20);
			}
		}
		break;
	case STATE_UI_GAME:
		if (uistate == STATE_UI_GAME)
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				if (state == STATE_BAI)
				{
					state = STATE_SHEN;
				}

			}
		}
		break;
	case STATE_UI_WIN:
		if (uistate == STATE_UI_WIN)
		{
			if (MouseHit())
			{
				MOUSEMSG mm = GetMouseMsg();

				switch (mm.uMsg)
				{
				case WM_LBUTTONDOWN:
					GameInit();
					Sleep(20);
					break;
				default:
					break;
				}
			}
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				ExitGame();
			}
		}
		break;
	default:
		break;
	}
}

void scoreCalculate(int moneyNum, int randNum, bool addMoney)
{
	if (addMoney == true)
	{
		money += (moneyNum + rand() % randNum);
	}
	else
	{
		money -= moneyNum;
	}
}
bool IsWin()
{
	for (int i = 0; i < N; i++)
	{
		if (ii[i].has_life == 0)return 0;
	}
	return true;
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

void gameLogic() {
	if (uistate == STATE_UI_GAME)
	{

		lx = 400 + sin(d) * lineLength;
		ly = 100 + cos(d) * lineLength;
		//要做延迟补偿
		drawHook(lx - 7, ly - 7);

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
				//改回摆的状态
				state = STATE_BAI;

				int temp = 0;
				//既然type都不等于这些值，那说明没有抓到，需要根据难度减分
				if (ii[temp].type != 0 || 1 || 2 || 3 || 4)
				{
					switch (gameLevel)
					{
					case 1:
						scoreCalculate(10, 0, false);
						break;
					case 2:
						scoreCalculate(30, 0, false);
						break;
					case 3:
						scoreCalculate(50, 0, false);
						break;
					case 4:
						scoreCalculate(100, 0, false);
						break;
					case 5:
						scoreCalculate(150, 0, false);
						break;
					default:
						scoreCalculate(10, 0, false);
						break;
					}
					
				}

				lineLength = 100;
				lineSpeed = -12;
			}
			break;
		default:
			break;
		}

		//记录获胜的条件
		for (int i = 0; i < N; i++) {
			if (ii[i].islife == 0) {
				ii[i].has_life = 1; // 标记存在islife等于1的元素  
			}
		}
		//获胜条件：IsWin函数返回true且分数大于0
		if (IsWin() == true && money > 0)
		{
			uistate = STATE_UI_WIN;
		}


	}
}

void drawGameUI()
{

	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 600);
	setbkmode(TRANSPARENT); //指定输出阴影和文本时的背景模式

	switch (uistate)
	{
	case STATE_UI_MENU:
		drawUIBG(0, 0);

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
		setfillcolor(RED);
		fillrectangle(260, 255 + uiflag * 80, 290, 285 + uiflag * 80);
		break;

	case STATE_UI_ABOUT:
		drawUIBG(0, 0);

		setcolor(WHITE);
		settextstyle(25, 0, L"宋体");
		outtextxy(50, 50, L"你说的对，但是《海里捞金》是由高羚翔自主研发的一款全新开放");
		outtextxy(50, 75, L"世界寻宝游戏。游戏发生在一个被称作「量子之海」的幻想世界，");
		outtextxy(50, 100, L"你将扮演一位名为「矿工」的神秘角色，收集神秘之物。");

		settextstyle(25, 0, L"宋体");
		outtextxy(50, 250, L"获胜条件：1、分数不为负数  2、采集完所有的矿物");
		settextstyle(15, 0, L"宋体");
		outtextxy(300, 450, L"由软件游戏3231班高羚翔制作，版权所有2024 , 保留所有权利。");
		break;
	case STATE_UI_GAME:
		setcolor(WHITE);
		settextstyle(55, 0, L"宋体");
		drawGame();
		break;
	case STATE_UI_WIN:
		drawUIBG(0, 0);

		setcolor(RED);
		settextstyle(55, 0, L"黑体");
		outtextxy(300, 175, L"你赢了！");

		setcolor(WHITE);
		settextstyle(25, 0, L"宋体");
		wsprintf(level, L"难度：%d", gameLevel);
		outtextxy(350, 300, level);

		setcolor(WHITE);
		settextstyle(25, 0, L"宋体");
		wsprintf(sc, L"金币：%d", money);
		outtextxy(350, 350, sc);

		setcolor(YELLOW);
		settextstyle(20, 0, L"宋体");
		outtextxy(235, 500, L"轻触屏幕任意区域重试，按Esc键退出");
		setcolor(YELLOW);
		settextstyle(15, 0, L"宋体");
		outtextxy(290, 540, L"选择继续挑战难度会增加哦 >_<");

		break;
	case STATE_UI_LOADING:
		drawUIBG(0, 0);

		setcolor(WHITE);
		settextstyle(55, 0, L"宋体");
		outtextxy(110, 100, L"原 来 你 也 玩 原 神");
		setcolor(WHITE);
		rectangle(150, 450, 650, 480);
		setcolor(WHITE);
		setfillcolor(WHITE);
		fillrectangle(151, 451, uilx, 479);
		
		uilx += 5;
		if (uilx >= 650) {
			uistate = STATE_UI_GAME;
			uilx = 150;
		}
		break;
	default:
		break;
	}
}

int main()
{
	
	loadRes();
	levelSelect();
	initgraph(800, 600);
	BeginBatchDraw();
	playBGSound(L"陈致逸,HOYO-MiX - 蒙德城繁忙的午后 Bustling Afternoon of Mondstadt.wav");
	while (1)
	{
		drawGameUI();
		ctrlGame();
		gameLogic();
		FlushBatchDraw();
		Sleep(50);
	}

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
