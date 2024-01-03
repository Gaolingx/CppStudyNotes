// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "stdio.h"
#include "graphics.h"
#include "time.h"
#define MAX_BOARD 10
#define MAX_SPACE 50
struct Board {

	int x;
	int y;
	int length;
	COLORREF color;

}board[MAX_BOARD];
//第一块板子
void initBoards()
{
	srand((unsigned)time(NULL));

	for (size_t i = 0; i < MAX_BOARD; i++)
	{
		board[i].x = rand() % getwidth();
		board[i].y = rand() % getheight();
		board[i].length = rand() % 50 + 50;
		board[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
}
/*
void initBoards() {
	for (int i = 0; i < MAX_BOARD; i++) {
		board[i].y--;
		if (board[i].y < 0)
		{

			board[i].y = MAX_BOARD * MAX_SPACE;
			board[i].x = rand() % (480 - 100);
			board[i].length = rand() % 50 + 50;
			board[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	    }
	}
}
*/
void drawGame() {
	for (int i = 0; i < MAX_BOARD; i++)
	{
		setfillcolor(board[i].color);
		fillrectangle(board[i].x, board[i].y, board[i].x + board[i].length, board[i].y + 5);

	}
}
void ctrlGame() {






}

void gameLogic() {


	for (int i = 0; i < MAX_BOARD; i++)

	{
		board[i].y--;
		if (board[i].y + 5 <= 0) {
			if (i == 0) {
				board[i].y = rand() %60 + 600;
			}
			else {
				board[i].y = board[i - 1].y + MAX_SPACE;
			}
			board[i].x = rand() % (480 - 100);
			board[i].length = rand() % 50 + 50;
			board[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		}
		board[i].x += 0;
		if (board[i].x > 480) {
			board[i].x = -board[i].length;
		}

	}
}
int main()
{


	initgraph(480, 760);
	BeginBatchDraw();

	initBoards();
	while (1) {


		cleardevice();
		drawGame();
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
