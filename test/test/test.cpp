// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "stdio.h"
#include "graphics.h"
#include "time.h"
#define MAX_BOARD 15
#define MAX_SPACE 50
TCHAR sc[20];
IMAGE bk;
IMAGE zj, zjhb;
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
	COLORREF color;
}Player;

int isGameOver = 0;
int score = 0;


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
		board[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	}
}
void initPlayer()
{
	Player.h = 8;
	Player.x = board[0].x + rand() % 50;
	Player.y = board[0].y - 12;
	Player.color = RED;
	Player.speed = 2;
}
void drawPlayer()
{
	setfillcolor(Player.color);
	solidcircle(Player.x, Player.y, Player.h);

}
int inBoard()
{
	for (int i = 0; i < MAX_BOARD; i++)
	{
		if (Player.x > board[i].x && Player.x < board[i].x + board[i].length &&
			Player.y + Player.h >= board[i].y - 2 && Player.y + Player.h <= board[i].y + 2)
		{
			if (!Player.passedBoard) {
				score++;
				Player.passedBoard = 1; // 设置标志，表示已经从一个板子上掉到另一个板子上
			}
			return 0;
		}
	}
	// 将未经过板子的标志重置
	Player.passedBoard = 0;
	return -1;
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
		setcolor(WHITE);
		settextstyle(30, 0, L"宋体");
		outtextxy(50, 50, L"Game Over");
		system("pause");



	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		Player.x--;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		Player.x++;
	}




}
void drawBoards() {
	for (int i = 0; i < MAX_BOARD; i++)
	{
		setfillcolor(board[i].color);
		fillrectangle(board[i].x, board[i].y, board[i].x + board[i].length, board[i].y + 5);

	}
}

void  moveBoards() {


	for (int i = 0; i < MAX_BOARD; i++)
	{

		board[i].y--;
		if (board[i].y < 0)
		{
			board[i].y = 15 * 50;
			board[i].x = rand() % (480 - 100);
			board[i].length = rand() % 50 + 50;
			board[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		}
	}

}
void drawScore() {
	settextcolor(WHITE);
	settextstyle(50, 0, L"黑体");
	wsprintf(sc, L"分数：%d", score);
	outtextxy(50, 30, sc);
}


int main()
{

	loadimage(&zj, L"rwqh.png", 1408, 768);
	loadimage(&zjhb, L"rwqhhb.png", 1408, 768);
	initgraph(480, 760);
	BeginBatchDraw();
	srand(time(NULL));
	initBoards();
	initPlayer();
	while (1) {


		cleardevice();
		drawBoards();
		moveBoards();
		drawPlayer();
		movePlayer();
		drawScore();
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
