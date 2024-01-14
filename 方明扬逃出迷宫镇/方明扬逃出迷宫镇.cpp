#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include"math.h"
#include"time.h"
#include"fmytcmgz.h"//迷宫地图的头文件
#include<iostream>//背景音乐
#include "windows.h"//背景音乐
#include "mmsystem.h"//背景音乐
#pragma comment(lib,"winmm.lib")
#define STATE_ABOUT 1
#define STATE_LOADING 2
#define STATE_GAME 3
#define STATE_MENU 4
#define WALL_COLOR RGB(80, 80, 80)
#define EXIT_COLOR RGB(255, 0, 0)
IMAGE bk, bk2;
IMAGE dt, rm;
IMAGE fmy,fmyblack;
IMAGE ys,ysblack;
IMAGE bj,klt ;
TCHAR c[3][100];
int state = STATE_GAME;
short(*map)[25];
int j, i, flag = 0;
int lx = 200;
int cx, cy;
int x = 1, y = 1;
int nx = 1, ny = 1, direction = 1;
int zx = 740, zy = 730;//钥匙位置
void drawGame()        
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 800);
	switch (state)
	{
	case STATE_MENU:
		setbkmode(TRANSPARENT);
		putimage(0, 0, 1000, 900, &bk, 0, 0, SRCCOPY);
		setcolor(BLACK);
		settextstyle(50, 0, L"宋体");//字体大小和字体颜色做调整
		outtextxy(380, 220, L"方明扬逃出迷宫镇");//文字的X，Y坐标 
		settextstyle(45, 0, L"宋体");//这里设置字体大小和字体风格		
		for (i = 0; i < 3; i++)
		{
			outtextxy(330, 250 + i * 45, c[i]);
		}
		setfillcolor(WHITE);
		fillrectangle(540, 280 + flag * 90, 750, 350 + flag * 90);
		outtextxy(550, 300, L"开始游戏");
		outtextxy(550, 390, L"游戏剧情");
		outtextxy(550, 480, L"退出游戏");
		break;
	case STATE_ABOUT:
		//游戏规则页面绘制
		setcolor(WHITE);
		setbkmode(TRANSPARENT);//使得字体在背景上面
		putimage(0, 0, 1000, 900, &bj, 0, 0, SRCCOPY);
		settextstyle(33, 0, L"黑体");
		outtextxy(50, 50, L"剧情介绍：");
		outtextxy(90, 100, L"退役军人方明扬在旅途中勿入了神秘的迷宫镇，");
		outtextxy(50, 150, L"镇上的老人面色凝重地告诉他：‘迷宫镇的人从");
		outtextxy(50, 200, L"来没有出去过，如有外人闯入，需要通过小镇古");
		outtextxy(50, 250, L"老的迷宫，找到迷宫中的三把钥匙，解开迷宫镇");
		outtextxy(50, 300, L"的封印，才能解开诅咒、让小镇重获自由。但是");
		outtextxy(50, 350, L"迷宫镇中的毒气会使得你的身体保持一种姿势，");
		outtextxy(50, 400, L"你只能以这种僵硬的姿势前进。’这三把钥匙代");
		outtextxy(50, 450, L"表了勇气、智慧、爱情，在寻找钥匙的过程中，");
		outtextxy(50, 500, L"方明扬逐渐领悟到这些品质的真谛。并结交了");
		outtextxy(50, 550, L"迷宫镇的好友人方明扬与朋友们克服重重困难，");
		outtextxy(50, 600, L"终于找到了三把钥匙，当方明扬将三把钥匙插");
		outtextxy(50, 650, L"入封印之地的石柱时，一道耀眼的光芒升起，");
		outtextxy(50, 700, L"小镇的诅咒被解开，人们重获新生。");
		outtextxy(90, 750, L" 而方明扬继续他的旅途，探访我大美中国!");
		break;
	case STATE_LOADING:
		putimage(0, 0, 1000, 900, &bk2, 0, 0, SRCCOPY);
		setcolor(WHITE);
		settextstyle(50, 0, L"宋体");
		outtextxy(100, 250, L"正在进入迷宫镇，请稍等...");
		//绘制进度条
		setcolor(BLACK);
		rectangle(150, 450, 650, 480);
		setcolor(WHITE);
		setfillcolor(WHITE);
		fillrectangle(151, 451, lx, 479);
		break;
	case STATE_GAME:
		//显示地图		
		map = map0;		
		setfillcolor(WHITE);
		fillrectangle(0, 0, 800, 800);
		for (i = max(0, cy - 3); i < min(30, cy + 3); i++)
			for (j = max(0, cx - 3); j < max(0, cx + 3); j++) {
				if (map[i][j] == 8)
				{
					//putimage(0, 0, 1000, 900, &klt, 0, 0, SRCCOPY);
					//fmy appear（黑白透明底图片的设置）
					putimage(nx + 35, ny + 35, 25, 25, &fmy, 0, 0, SRCINVERT);
					putimage(nx + 35, ny + 35, 25, 25, &fmyblack, 0, 0, SRCAND);
					putimage(nx + 35, ny + 35, 25, 25, &fmy, 0, 0, SRCINVERT);
					//ys appear
					putimage(zx, zy, 35, 35, &ys, 0, 0, SRCINVERT);
					putimage(zx, zy, 35, 35, &ysblack, 0, 0, SRCAND);
					putimage(zx, zy, 35, 35, &ys, 0, 0, SRCINVERT);

				}
				else if (map[i][j] != 0)
				{
					putimage(0 + j * 32, 0 + i * 32, 32, 32, &dt, (map[i][j]+10) % 8 * 32, (int)((map[i][j]+10) / 6) * 32, SRCCOPY);
				}
			}
	}
}
void ctrlGame()
{
	switch (state)
	{
	case STATE_MENU:
		//界面的键盘控制
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			flag--;
			if (flag == -1)flag = 2;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			flag = (flag + 1) % 3;
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (flag == 0)state = STATE_LOADING;
			else if (flag == 1)state = STATE_ABOUT;
			else exit(0);
		}
		break;
	case STATE_ABOUT:
		//由界面切换至游戏
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			state = STATE_MENU;
		}
		break;
	case STATE_GAME://控制方明扬移动(墙壁无法阻挡方明扬）
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			/*
			if (map[y][x - 1]!= 0)//nx - 1 >= 0 && 
			{
				ny -= 10;//控制人物行进速度
				direction = 3;
			}
			*/
			if (map0[cy - 1][cx] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy - 1][cx] = 8;
				cy--;
				ny -= 32;
			}
			if (map0[cy + 1][cx] == 10)
			{
				map0[cy][cx] = 0;
				map0[1][1] = 8;
				cy = 1;
				cx = 1;
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			/*
			if (map[y][x + 1]== 0)// nx + 1 <= 49 &&
			{
			ny += 10;
			direction = 0;
			}
			*/
			if (map0[cy + 1][cx] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy + 1][cx] = 8;
				cy++;
				ny += 32;
			}
			if (map0[cy + 1][cx] == 10)
			{
				map0[cy][cx] = 0;
				map0[1][1] = 8;
				cy = 1;
				cx = 1;
			}
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			/*
			if (map[y - 1][x] != 0)//ny - 1 >= 0 && 
			{
				nx -= 10;
				direction = 1;
			}
			*/
			if (map0[cy][cx - 1] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy][cx - 1] = 8;
				cx--;
				nx -= 32;

			}
			if (map0[cy + 1][cx] == 10)
			{
				map0[cy][cx] = 0;
				map0[1][1] = 8;
				cy = 1;
				cx = 1;
			}
		}
		
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			/*
			if (map[y + 1][x] ==0)// ny + 1 <= 49 &&
			{
				nx += 10;
				direction = 2;
			}
			*/
			if (map0[cy][cx + 1] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy][cx + 1] = 8;
				cx++;
				nx += 32;

			}
			if (map0[cy + 1][cx] == 10)
			{
				map0[cy][cx] = 0;
				map0[1][1] = 8;
				cy = 1;
				cx = 1;
			}
		}
		
	}
}
void gameLogic()
{
	//进度条移动
	switch (state)
	{
	case STATE_LOADING:
		lx += 15;
		if (lx >= 650)
		{
			state = STATE_GAME;
		}
		break;
	}
}
void drawfmy(IMAGE fmy)
{
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			if (map0[i][j] != 0)
			{
				putimage(0 + j * 16, 0 + i * 16, &fmy, SRCCOPY);
			}
		}	
}
int main()
{
	//PlaySound(L"徐梦圆 - The Chinese Zither.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	initgraph(800, 800);
	loadimage(&bk, L"游戏界面2.jpg", 1000, 900);
	loadimage(&dt, L"TEST2.BMP", 512, 1000);//迷宫地图图片
	loadimage(&bk2, L"背景.png");
	loadimage(&fmy, L"方明扬2.0.png", 27, 27);
	loadimage(&fmyblack, L"方明扬黑白图.png", 25, 25);
	loadimage(&ys, L"钥匙.png", 30, 30);//后面的数字调节图片大小
	loadimage(&ysblack, L"钥匙黑白图.png", 30, 30);
	loadimage(&bj, L"背景2.png",1000, 900);
	loadimage(&klt, L"骷髅头.jpg", 1000, 900);
	BeginBatchDraw();
	cx = 1;
	cy = 1;
	map = map1;
	while (1)
	{
		drawGame();
		ctrlGame();
		gameLogic();
		FlushBatchDraw();
		Sleep(125);
	}
	EndBatchDraw();
	closegraph();
}
