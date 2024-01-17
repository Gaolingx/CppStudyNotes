// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "stdio.h"
#include "graphics.h"
#include "time.h"
#include "windows.h"
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")

#define STATE_UI_MENU 10
#define STATE_UI_ABOUT 11
#define STATE_UI_LOADING 12
#define STATE_UI_GAME 13
#define STATE_UI_WIN 14
#define MAX_BOARD 15
#define MAX_SPACE 50
TCHAR sc[20];

IMAGE bg;

TCHAR uic[3][100] = { L"开始游戏",L"关于游戏",L"退出游戏" };

int uistate = STATE_UI_MENU;
int uii, uiflag = 0;
int uilx = 150;

struct Board {

	int x;
	int y;
	int length;

	COLORREF color;

}board[MAX_BOARD];
struct Player
{
	int x;
	int y;
	int h;
	int speed;
	bool passedBoard;
	bool onRedBoard;

	COLORREF color;
}Player;

int isGameOver = 0;
int score = 0;
int redBoardProbability;

void loadImg()
{
	loadimage(&bg, L"bg.png", 480, 720);
}
// 新增更新红色板子概率的函数
void updateRedBoardProbability() {
	// 根据需要更新红色板子出现的概率
	// 例如，可以根据当前分数调整概率，使得分数越高，红色板子出现的概率越大
	redBoardProbability = min(0.5, redBoardProbability + 0.01 * score);
}

void initBoards() {
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX_BOARD; i++) {
		if (i == 0) {
			board[i].y = rand() % 100 + 600;
		}
		else {
			board[i].y = board[i - 1].y + MAX_SPACE;
		}
		board[i].x = rand() % (480 - 100);
		board[i].length = rand() % 50 + 50;
		// 根据红色板子的概率设置板子颜色
		board[i].color = (rand() % 100 < redBoardProbability) ? RED : RGB(rand() % 256, rand() % 256, rand() % 256);

	}
}
void initPlayer()
{
	Player.h = 8;
	Player.x = board[0].x + rand() % 50;
	Player.y = board[0].y - 150;
	Player.color = RED;
	Player.speed = 4;
}
void drawPlayer()
{
	setfillcolor(Player.color);
	solidcircle(Player.x, Player.y, Player.h);

}
void drawBoards() {
	for (int i = 0; i < MAX_BOARD; i++)
	{
		setfillcolor(board[i].color);
		fillrectangle(board[i].x, board[i].y, board[i].x + board[i].length, board[i].y + 5);

	}
}
void drawScore() {
	settextcolor(WHITE);
	settextstyle(50, 0, L"黑体");
	wsprintf(sc, L"分数：%d", score);
	outtextxy(50, 30, sc);
}
void drawGame()
{
	putimage(0, 0, &bg, SRCCOPY);
	drawScore();
	drawBoards();
	drawPlayer();

}
void drawGameUI()
{

	setfillcolor(BLACK);
	fillrectangle(0, 0, 480, 760);

	switch (uistate)
	{
	case STATE_UI_MENU:
		setcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		settextstyle(55, 0, L"宋体");
		outtextxy(100, 100, L"下 一 百 层");
		setcolor(GREEN);
		settextstyle(20, 0, L"宋体");
		outtextxy(110, 200, L"冷狐无伤版 v1.0.11");
		settextstyle(32, 0, L"宋体");
		for (uii = 0; uii < 3; uii++) {
			outtextxy(200, 250 + uii * 80, uic[uii]);
		}
		setfillcolor(BLACK);
		fillrectangle(160, 255 + uiflag * 80, 190, 285 + uiflag * 80);
		break;

	case STATE_UI_ABOUT:
		setcolor(WHITE);
		settextstyle(25, 0, L"宋体");
		outtextxy(50, 50, L"这是一个小球不断下落然后得分的游戏");

		break;
	case STATE_UI_GAME:
		setcolor(WHITE);
		settextstyle(55, 0, L"宋体");
		drawGame();
		break;
	case STATE_UI_WIN:

		setcolor(RED);
		settextstyle(55, 0, L"黑体");
		outtextxy(110, 175, L"游戏结束！");

		settextcolor(WHITE);
		settextstyle(50, 0, L"黑体");
		wsprintf(sc, L"分数：%d", score);
		outtextxy(150, 350, sc);

		setcolor(YELLOW);
		settextstyle(20, 0, L"宋体");
		outtextxy(75, 500, L"轻触屏幕任意区域重试，按Esc键退出");

		break;
	case STATE_UI_LOADING:
		setcolor(WHITE);
		settextstyle(55, 0, L"宋体");
		outtextxy(125, 100, L"Loading...");
		setcolor(WHITE);
		rectangle(50, 450, 450, 480);
		setcolor(WHITE);
		setfillcolor(WHITE);
		fillrectangle(51, 451, uilx, 479);

		uilx += 5;
		if (uilx >= 450) {
			uistate = STATE_UI_GAME;
			uilx = 150;
		}
		break;
	default:
		break;
	}
}

int inBoard() {
	for (int i = 0; i < MAX_BOARD; i++) {
		// 检测小球与板子的碰撞
		if (Player.x > board[i].x && Player.x < board[i].x + board[i].length &&
			Player.y + Player.h >= board[i].y - 2 && Player.y + Player.h <= board[i].y + 2)
		{

			if (!Player.passedBoard)
			{
				score++;
				Player.passedBoard = true;
			}
			// 判断板子颜色是否为红色
			if (board[i].color == RED) {
				if (!Player.onRedBoard) {
					score--;  // 小球踩在红色板子上，扣一分
					Player.onRedBoard = true;
				}
			}
			else {
				Player.onRedBoard = false;
			}
			return 0;
		}
	}
	Player.passedBoard = false;
	Player.onRedBoard = false;
	return -1;
}

void ctrlGame()
{

	if (GetAsyncKeyState(VK_LEFT))
	{
		Player.x--;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		Player.x++;
	}

	if (uistate == STATE_UI_MENU || STATE_UI_ABOUT)
	{

		switch (uistate)
		{
		case STATE_UI_MENU:
			if (GetAsyncKeyState(VK_UP) & 0x8000) {
				Sleep(50);
				uiflag--;
				if (uiflag == -1)
				{
					uiflag = 2;
				}
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
				Sleep(50);
				uiflag = (uiflag + 1) % 3;
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
					exit(0);
				}
			}
			break;
		case STATE_UI_ABOUT:
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
				uistate = STATE_UI_MENU;
			}
			break;
		case STATE_UI_GAME:
			if (GetAsyncKeyState(VK_LEFT))
			{
				Player.x--;
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				Player.x++;
			}
		case STATE_UI_WIN:

			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				exit(0);
			}
		default:
			break;
		}
	}
}

void movePlayer()
{

	if (inBoard() != -1)
	{
		Player.y--;
		Player.speed = 2;

	}
	else {
		Player.y += Player.speed;
		if (Player.speed <= 2)
			Player.speed++;

	}
	if (Player.y > 740 || Player.y < 0) {
		setfillcolor(BLACK);
		uistate = STATE_UI_WIN;

	}


}

void  moveBoards() {


	for (int i = 0; i < MAX_BOARD; i++)
	{

		board[i].y--;
		if (board[i].y < 0)
		{
			board[i].y = 20 * 50;
			board[i].x = rand() % (480 - 100);
			board[i].length = rand() % 50 + 50;
			board[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		}
	}

}

void gameLogic()
{
	updateRedBoardProbability();
	if (uistate == STATE_UI_GAME)
	{
		moveBoards();
		movePlayer();
	}

}

int main()
{


	PlaySound(L"bgm.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	initgraph(480, 760);
	BeginBatchDraw();
	loadImg();
	srand(time(NULL));
	initBoards();
	initPlayer();
	while (1) {


		cleardevice();
		drawGameUI();
		ctrlGame();
		gameLogic();

		FlushBatchDraw();
		Sleep(20);
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
