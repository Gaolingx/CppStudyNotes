#include <graphics.h>
#include "stdlib.h"
#include "math.h"
#include "time.h"
#define  STATE_MENU 0
#define  STATE_ABOUT 1
#define  STATE_LOADING 2
#define  STATE_GAME 3
#define  PLAYER 0
#define  NPC 1
struct Bullet {
	int x;
	int y;
	int vx;
	int vy;
	COLORREF c;
	int owner;
	int islife = 0;
}b[1500];
struct npc
{
	int x;
	int y;
	int vx;
	int vy;
	int direction;
	int hp;
	int islife = 0;
	COLORREF c;
	int time = 0;
	int ischange = 0;
}n[200];
struct  skill
{
	int sc = 3;
	int skillTime = 0;
	npc sk[20];
}s;
int state = STATE_GAME;
TCHAR c[3][100] = { L"开始游戏",L"关于游戏",L"退出游戏" };
int i, lx = 150, flag = 0;
int mpx = 400, mpy = 500;
int mytype = 0;
int gameTime = 0;
int isSkill = 0;

int collide1(Bullet b) {
	if (sqrt((mpx - b.x) * (mpx - b.x) + (mpy - b.y) * (mpy - b.y)) < 20) {
		return 1;
	}
	else
		return 0;
}
int collide2(npc b) {
	if (sqrt((mpx - b.x) * (mpx - b.x) + (mpy - b.y) * (mpy - b.y)) < 20) {
		return 1;
	}
	else
		return 0;
}
int collide3(Bullet b, npc n) {
	if (sqrt((n.x - b.x) * (n.x - b.x) + (n.y - b.y) * (n.y - b.y)) < 20) {
		return 1;
	}
	else
		return 0;
}
int collide4(Bullet b, Bullet n) {
	if (sqrt((n.x - b.x) * (n.x - b.x) + (n.y - b.y) * (n.y - b.y)) < 10) {
		return 1;
	}
	else
		return 0;
}

void createNPC(int x, int y, int vx, int vy, COLORREF c, int direction) {
	int i;
	for (i = 0; i < 200; i++) {
		if (n[i].islife == 0) {
			n[i].islife = 1;
			n[i].x = x;
			n[i].y = y;
			n[i].vx = vx;
			n[i].vy = vy;
			n[i].c = c;
			n[i].direction = direction;
			break;
		}
	}
}

void createBullet(int x, int y, int vx, int vy, int owner, COLORREF c) {
	int i;
	for (i = 0; i < 1500; i++) {
		if (b[i].islife == 0) {
			b[i].islife = 1;
			b[i].x = x;
			b[i].y = y;
			b[i].vx = vx;
			b[i].vy = vy;
			b[i].owner = owner;
			b[i].c = c;
			break;
		}
	}
}
void moveBullet() {
	int i;
	for (i = 0; i < 1500; i++) {
		if (b[i].islife == 1) {
			b[i].x += b[i].vx;
			b[i].y += b[i].vy;
			if (b[i].x < -500 || b[i].x>1300 || b[i].y > 1100 || b[i].y < -500) {
				b[i].islife = 0;
			}
			if (b[i].owner == NPC) {
				if (collide1(b[i]) == 1) {
					b[i].islife = 0;
				}
			}
			if (b[i].owner == PLAYER) {
				for (int j = 0; j < 200; j++) {
					if (n[j].islife == 1) {
						if (collide3(b[i], n[j]) == 1) {
							b[i].islife = 0;
							n[j].islife = 0;
							break;
						}
					}
				}
				for (int k = 0; k < 1500; k++) {
					if (b[k].islife == 1 && b[k].owner == NPC) {
						if (collide4(b[i], b[k]) == 1) {
							b[i].islife = 0;
							b[k].islife = 0;
							break;
						}
					}
				}
			}

		}
	}
}
void drawBullet() {
	int i = 0;
	for (i = 0; i < 1500; i++) {
		if (b[i].islife == 1) {
			setcolor(b[i].c);
			setfillcolor(b[i].c);
			fillcircle(b[i].x, b[i].y, 5);
		}
	}
}
void drawPlane(int x, int y, COLORREF c, int direction) {
	setcolor(c);
	switch (direction)
	{
	case 0://上
		line(x - 10, y, x + 10, y);
		line(x - 5, y + 8, x + 5, y + 8);
		line(x, y - 8, x, y + 8);
		break;
	case 1://下
		line(x - 10, y, x + 10, y);
		line(x - 5, y - 8, x + 5, y - 8);
		line(x, y - 8, x, y + 8);
		break;
	case 2:
		line(x, y - 10, x, y + 10);
		line(x + 8, y - 5, x + 8, y + 5);
		line(x - 8, y, x + 8, y);
		break;
	case 3:
		line(x, y - 10, x, y + 10);
		line(x - 8, y - 5, x - 8, y + 5);
		line(x - 8, y, x + 8, y);
		break;
	default:
		break;
	}
}


void createSkill() {
	s.sc--;
	for (int i = 0; i < 20; i++) {
		s.sk[i].islife = 1;
		s.sk[i].x = mpx + cos(0.314 * i) * 40;
		s.sk[i].y = mpy + sin(0.314 * i) * 40;
		s.sk[i].c = YELLOW;
		s.sk[i].direction = 0;
	}
}
void drawSkill() {
	int i = 0;
	for (i = 0; i < 20; i++) {
		if (s.sk[i].islife == 1) {
			drawPlane(s.sk[i].x, s.sk[i].y, s.sk[i].c, s.sk[i].direction);
		}
	}
}
void moveSkill() {
	int flag = 0;
	s.skillTime++;
	if (s.skillTime < 100) {
		for (int i = 0; i < 20; i++) {
			s.sk[i].x = mpx + cos(0.314 * i) * 40;
			s.sk[i].y = mpy + sin(0.314 * i) * 40;
		}
	}
	else if (s.skillTime == 100) {
		for (int i = 0; i < 20; i++) {
			s.sk[i].vx = cos(0.314 * i) * -20;
			s.sk[i].vy = sin(0.314 * i) * -20;
		}
	}
	else {
		for (int i = 0; i < 20; i++) {
			s.sk[i].x += s.sk[i].vx;
			s.sk[i].y += s.sk[i].vy;
		}
	}

	for (int i = 0; i < 20; i++) {
		if (s.sk[i].x < 800 && s.sk[i].x>0 && s.sk[i].y > 0 && s.sk[i].y < 600) {
			flag = 1;
			break;
		}
	}
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 1500; j++) {
			if (b[j].islife == 1 && b[j].owner == NPC) {
				if (collide3(b[j], s.sk[i]) == 1) {
					b[j].islife = 0;
				}
			}
		}
	}

	if (flag == 0)isSkill = 0;
}

void drawNPC() {
	int i;
	for (i = 0; i < 200; i++) {
		if (n[i].islife == 1) {
			drawPlane(n[i].x, n[i].y, n[i].c, n[i].direction);
		}
	}
}
void moveNPC() {
	int i;
	double dd;
	for (i = 0; i < 200; i++) {
		if (n[i].islife == 1) {
			n[i].x += n[i].vx;
			n[i].y += n[i].vy;
			n[i].time++;
			if (n[i].y > 300 && n[i].y < 350 && n[i].ischange == 0) {
				n[i].ischange = 1;
				dd = atan2(n[i].y - mpy, n[i].x - mpx);
				n[i].vx = cos(dd) * -15;
				n[i].vy = sin(dd) * -15;
				if (n[i].vy < 0)n[i].direction = 0;
				else n[i].direction = 1;
			}
			if (collide2(n[i]) == 1) {
				n[i].islife = 0;
				n[i].ischange = 0;
				n[i].time = 0;
				break;
			}
			if (n[i].x < -300 || n[i].x>1100 || n[i].y < -300 || n[i].y>900) {
				n[i].islife = 0;
				n[i].ischange = 0;
				n[i].time = 0;
			}
			if (n[i].time % 30 == 0) {
				dd = atan2(n[i].y - mpy, n[i].x - mpx);
				createBullet(n[i].x, n[i].y, cos(dd) * -18, sin(dd) * -18, NPC, LIGHTBLUE);
			}
		}
	}
}
void drawGame()
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 600);
	switch (state)
	{
	case STATE_MENU:
		drawPlane(650, 125, YELLOW, 0);
		setcolor(YELLOW);
		settextstyle(60, 0, L"楷体");
		outtextxy(180, 100, L"博 雅 小 战 机");
		for (i = 0; i < 3; i++) {
			setcolor(YELLOW);
			if (flag != i) {
				settextstyle(36, 0, L"楷体");
			}
			else {
				settextstyle(50, 0, L"楷体");
			}
			outtextxy(320, 300 + 80 * i, c[i]);
		}
		/*setcolor(YELLOW);
		circle(265 ,  315 + flag * 80, 20);*/
		//rectangle(250, 305+flag*80, 280, 335+flag*80);
		break;
	case STATE_ABOUT:
		setcolor(YELLOW);
		settextstyle(40, 0, L"楷体");
		outtextxy(80, 80, L"这是一款以华丽弹幕为特色的飞行射击类游戏");
		outtextxy(80, 180, L"制作人：游戏3231班");

		break;
	case STATE_LOADING:
		setcolor(YELLOW);
		settextstyle(60, 0, L"楷体");
		outtextxy(180, 100, L"博 雅 小 战 机");
		rectangle(150, 450, 650, 480);
		setcolor(RED);
		setfillcolor(RED);
		fillrectangle(151, 451, lx, 479);
		break;
	case STATE_GAME:


		drawBullet();
		drawNPC();
		if (isSkill == 1) {
			drawSkill();
		}
		switch (mytype)
		{
		case 0:
			drawPlane(mpx, mpy, YELLOW, 0);
			break;
		case 1:
			drawPlane(mpx, mpy, RED, 0);
			break;
		case 2:
			drawPlane(mpx, mpy, BROWN, 0);
			break;
		}

		break;

	}
}
void ctrlGame()
{
	switch (state)
	{
	case STATE_MENU:
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			flag--;
			if (flag == -1)flag = 2;

		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			flag = (flag + 1) % 3;

		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			if (flag == 0)state = STATE_LOADING;
			else if (flag == 1)state = STATE_ABOUT;
			else exit(0);
		}
		break;
	case STATE_ABOUT:
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			state = STATE_MENU;
		}
		break;
	case STATE_GAME:
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			mpy -= 5;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			mpy += 5;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			mpx -= 5;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			mpx += 5;
		}
		if (GetAsyncKeyState('Q') & 0x8000) {
			mytype = (mytype + 1) % 3;
		}
		if (GetAsyncKeyState('E') & 0x8000) {
			if (isSkill == 0 && s.sc > 0) {
				isSkill = 1;
				s.skillTime = 0;
				createSkill();
			}
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			switch (mytype)
			{
			case 0:
				createBullet(mpx, mpy, 0, -10, PLAYER, YELLOW);
				createBullet(mpx + 10, mpy, 0, -10, PLAYER, YELLOW);
				createBullet(mpx - 10, mpy, 0, -10, PLAYER, YELLOW);
				createBullet(mpx + 20, mpy, 0, -10, PLAYER, YELLOW);
				createBullet(mpx - 20, mpy, 0, -10, PLAYER, YELLOW);
				createBullet(mpx + 30, mpy, 0, -10, PLAYER, YELLOW);
				createBullet(mpx - 30, mpy, 0, -10, PLAYER, YELLOW);
				break;
			case 1:
				createBullet(mpx, mpy, 0, -12, PLAYER, RED);
				createBullet(mpx, mpy, 2, -11, PLAYER, RED);
				createBullet(mpx, mpy, -2, -11, PLAYER, RED);
				createBullet(mpx, mpy, 4, -10, PLAYER, RED);
				createBullet(mpx, mpy, -4, -10, PLAYER, RED);
				createBullet(mpx, mpy, 6, -9, PLAYER, RED);
				createBullet(mpx, mpy, -6, -9, PLAYER, RED);
				break;
			case 2:
				for (double i = 0; i < 20; i++) {
					createBullet(mpx, mpy, -15 * cos(0.314 * i), -15 * sin(0.314 * i), PLAYER, RGB(250 - i * 8, 50, 50 + i * 10));
				}
				/*createBullet(mpx, mpy, 0, -12, PLAYER, BROWN);
				createBullet(mpx, mpy, 4, -11, PLAYER, BROWN);
				createBullet(mpx, mpy, -4, -11, PLAYER, BROWN);
				createBullet(mpx, mpy, 8, -10, PLAYER, BROWN);
				createBullet(mpx, mpy, -8, -10, PLAYER, BROWN);
				createBullet(mpx, mpy, 2, 12, PLAYER, BROWN);
				createBullet(mpx, mpy, -2, 12, PLAYER, BROWN);
				createBullet(mpx, mpy, 4, 12, PLAYER, BROWN);
				createBullet(mpx, mpy, -4, 12, PLAYER, BROWN);*/
				break;
			}

		}

		break;
	}
}
void gameLogic()
{
	switch (state)
	{
	case STATE_LOADING:
		lx += 15;
		if (lx >= 650) {
			lx = 150;
			state = STATE_GAME;
		}
		break;
	case STATE_GAME:
		gameTime++;
		if (gameTime % 10 == 0) {
			createNPC(rand() % 790, -10 - rand() % 200, 0, 8, WHITE, 1);
		}
		if (gameTime % 101 == 0) {
			createNPC(800, 200, -10, 0, WHITE, 2);
			createNPC(830, 200, -10, 0, WHITE, 2);
			createNPC(860, 200, -10, 0, WHITE, 2);
			createNPC(890, 200, -10, 0, RED, 2);
		}
		if (gameTime % 80 == 0) {
			createNPC(rand() % 790, 610, 0, -15, RGB(239, 169, 190), 0);
		}
		moveNPC();
		moveBullet();
		if (isSkill == 1) {
			moveSkill();
		}
		break;
	}
}

int main()
{

	initgraph(800, 600);
	BeginBatchDraw();

	while (1)
	{
		//游戏视图模块
		drawGame();
		//游戏控制模块
		ctrlGame();
		//游戏逻辑模块
		gameLogic();

		FlushBatchDraw();
		Sleep(40);
	}
	EndBatchDraw();
	closegraph();
}
