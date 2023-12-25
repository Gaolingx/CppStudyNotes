// ConsoleApplication8.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include "graphics.h"
#include <stdlib.h>
#include <time.h>
#include "dt.h"

IMAGE bk;
IMAGE zj, zjhb;
IMAGE an, dr;
struct npc {
	int x;
	int y;
	int vx;
	int direction;
	IMAGE* img;
	int islife = 1;
	int isfall = 1;
	int frame = 0;
}n[5] = { {420,430,5,0,&an},
		{1120,300,5,0,&dr},
		{1320,440,5,0,&an},
		{1820,330,5,0,&dr},
		{2420,230,5,0,&an}
};
int* frameArray;
int endframe = 3;
int frame = 0;
static int lju[11] = { 54 };
static int rju[11] = { 55 };
static int ljd[11] = { 160 };
static int rjd[11] = { 169 };
static int lstand[11] = { 10,9,8 };
static int rstand[11] = { 11,12,13 };
static int lrun[11] = { 32,31,30,29,28,27,26,25 };
static int rrun[11] = { 33,34,35,36,37,38,39,40 };
int lattactk[11] = { 186,185,184,183,182,181,180,179,178,177,176 };
int rattactk[11] = { 187,188,189,190,191,192,193,194,195,196,197 };
int isAttack = 0, isJump = 0;
int zx = 50, zy = 500;
int zvx, zvy;
int lmx = 0;
int zdirection = 0;//0表示右1表示左

void drawMap(IMAGE bk, int maxRow, int maxCol) 
{
	int i, j;
	for (i = 0; i < maxRow; i++)
		for (j = 0; j < maxCol; j++) {
			putimage(lmx + j * 16, 0 + i * 16, 16, 16, &bk,
				(map0[i][j] - 1) % 12 * 16, (map0[i][j] - 1) / 12 * 16, SRCCOPY);
		}
}
void drawNpc() 
{
	int i;
	for (i = 0; i < 5; i++) {
		if (n[i].islife == 1) {
			putimage(n[i].x + lmx, n[i].y, 32, 32, n[i].img,
				n[i].frame * 32, n[i].direction * 32, SRCCOPY);
		}
	}
}
void loadRes()
{
	loadimage(&bk, L"ditu1.bmp");
	loadimage(&zj, L"rwqh.png", 1408, 768);
	loadimage(&zjhb, L"rwqhhb.png", 1408, 768);
	loadimage(&an, L"080-Angel02.bmp", 128, 128);
	loadimage(&dr, L"099-Monster13.bmp", 128, 128);
}

void Init()
{
	initgraph(800, 640);
	frameArray = rattactk;
	endframe = 11;

}

void drawGame()
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 640);
	drawMap(bk, 40, 200);
	drawNpc();
	putimage(zx, zy, 64, 64, &zj,
		0 + frameArray[frame] % 22 * 64, 0 + frameArray[frame] / 22 * 64, SRCINVERT);
	putimage(zx, zy, 64, 64, &zjhb,
		0 + frameArray[frame] % 22 * 64, 0 + frameArray[frame] / 22 * 64, SRCAND);
	putimage(zx, zy, 64, 64, &zj,
		0 + frameArray[frame] % 22 * 64, 0 + frameArray[frame] / 22 * 64, SRCINVERT);
}

void GameControl()
{
	if (isJump == 0 && zx > 0 && GetAsyncKeyState(VK_LEFT) & 0x8000) {
		zdirection = 1;
		frameArray = lrun;
		endframe = 8;
		if (lmx < 0 && zx < 400)
			lmx += 8;
		else
			zx -= 8;
	}
	if (isJump == 0 && zx < 736 && GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		zdirection = 0;
		frameArray = rrun;
		endframe = 8;
		if (lmx > -2400 && zx > 400) {
			lmx -= 8;
		}
		else {
			zx += 8;
		}
	}
	if (isJump == 0 && isAttack == 0 && GetAsyncKeyState(VK_SPACE) & 0x8000) {
		isAttack = 1;
		if (zdirection == 0) {
			frameArray = rattactk;
			endframe = 11;
		}
		else {
			frameArray = lattactk;
			endframe = 11;
		}
	}
	if (isJump == 0 && isAttack == 0 && GetAsyncKeyState(VK_UP) & 0x8000) {
		isJump = 1;
		if (zdirection == 0) {
			frameArray = rju;
		}
		else
			frameArray = lju;
		if (endframe == 3) {
			zvx = 0;
			zvy = -22;
		}
		if (endframe == 8) {
			if (zdirection == 0) {
				zvx = 8;
				zvy = -24;
			}
			else {
				zvx = -8;
				zvy = -24;
			}
		}
		endframe = 1;
	}
}

void moveNpc() 
{
	int i;
	int row, col;
	for (i = 0; i < 5; i++) {
		if (n[i].islife == 1) {
			n[i].frame = (n[i].frame + 1) % 4;
			if (n[i].isfall == 1) {
				n[i].y += 6;
				row = (n[i].y + 32) / 16;
				col = (n[i].x + 16) / 16;
				if (map0[row][col] != 0) {
					n[i].isfall = 0;
					n[i].direction = 2;
				}
			}
			else {
				n[i].x += n[i].vx;
				row = (n[i].y + 32) / 16;
				col = (n[i].x + 16) / 16;
				if (map0[row][col] == 0) {
					if (n[i].direction == 2)
						n[i].direction = 1;
					else
						n[i].direction = 2;

					n[i].vx *= -1;
				}

			}
		}
	}
}

void GameLogic()
{
	int row, col;
	moveNpc();
	frame = (frame + 1) % endframe;
	if (isAttack == 1 && frame == 0)isAttack = 0;
	if (isAttack == 0) {
		zy += 5;
		row = (zy + 64) / 16;
		col = (zx + 32 - lmx) / 16;
		if (map0[row][col] != 0) {
			zy -= 5;
			if (zdirection == 0) {
				frameArray = rstand;
				endframe = 3;
			}
			else {
				frameArray = lstand;
				endframe = 3;
			}
		}
	}
	if (isJump == 1) {
		/*zx += zvx;*/
		if (zdirection == 0) {
			if (lmx > -2400 && zx > 400) {
				lmx -= zvx;
			}
			else {
				zx += zvx;
			}
		}
		else {
			if (lmx < 0 && zx < 400) {
				lmx -= zvx;
			}
			else {
				zx += zvx;
			}
		}

		zy += zvy;
		zvy += 1;
		if (zvy > 0) {
			if (zdirection == 0) {
				frameArray = rjd;
				endframe = 1;
			}
			else {
				frameArray = ljd;
				endframe = 1;
			}
			row = (zy + 64) / 16;
			col = (zx + 32 - lmx) / 16;
			if (map0[row][col] != 0) {
				zy -= 5;
				isJump = 0;
			}
		}
	}
}

int main()
{
	Init();
	BeginBatchDraw();
	loadRes();

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
