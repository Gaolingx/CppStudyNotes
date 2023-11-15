// ConsoleApplication8.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <graphics.h>
#include <stdio.h>

char blackFirst;
#define PLAYER_1 1
#define PLAYER_2 2
int player;
int cx = 6, cy = 6;
static int map[11][11];
int i, j;
int isWin = 0;

int judgeWin() {
	int flag = 0;
	int count = 0;
	//水平方向
	count = 1;
	if (cx > 0)
		for (i = cx - 1; i >= 0; i--) {
			if (map[cy][i] == player)count++;
			else break;
		}
	if (cx < 10) {
		for (i = cx + 1; i <= 10; i++) {
			if (map[cy][i] == player)count++;
			else break;
		}
	}
	if (count >= 5)flag = 1;

	//垂直方向
	count = 1;
	if (cy > 0)
		for (i = cy - 1; i >= 0; i--) {
			if (map[i][cx] == player)count++;
			else break;
		}
	if (cy < 10) {
		for (i = cy + 1; i <= 10; i++) {
			if (map[i][cx] == player)count++;
			else break;
		}
	}
	if (count >= 5)flag = 1;

	//\方向
	count = 1;
	if (cy > 0 && cx > 0)
		for (i = cy - 1, j = cx - 1; i >= 0 && j >= 0; i--, j--) {
			if (map[i][j] == player)count++;
			else break;
		}
	if (cy < 10 && cx < 10) {
		for (i = cy + 1, j = cx + 1; i <= 10 && j <= 10; i++, j++) {
			if (map[i][j] == player)count++;
			else break;
		}
	}
	if (count >= 5)flag = 1;

	// /方向
	count = 1;
	if (cy > 0 && cx < 10)
		for (i = cy - 1, j = cx + 1; i >= 0 && j <= 10; i--, j++) {
			if (map[i][j] == player)count++;
			else break;
		}
	if (cy < 10 && cx >0) {
		for (i = cy + 1, j = cx - 1; i <= 10 && j >= 0; i++, j--) {
			if (map[i][j] == player)count++;
			else break;
		}
	}
	if (count >= 5)flag = 1;

	return flag;
}
void initMap()
{
	int i, j;
	for (i = 0; i < 11; i++)
	{
		for (j = 0; j < 11; j++)
		{
			map[i][j] = 0;
		}
		
	}
}
void showPlayer(int player) {
	setcolor(YELLOW);
	settextstyle(40, 0, L"楷体");
	if (player == PLAYER_1) {
		outtextxy(600, 200, L"黑");
	}
	if (player == PLAYER_2) {
		outtextxy(600, 200, L"白");
	}
	outtextxy(600, 250, L"方");
	outtextxy(600, 300, L"下");
	outtextxy(600, 350, L"棋");
	if (isWin == 1) {
		if (player == PLAYER_1) {
			outtextxy(650, 200, L"黑");
		}
		if (player == PLAYER_2) {
			outtextxy(650, 200, L"白");
		}
		outtextxy(650, 250, L"方");
		outtextxy(650, 300, L"胜");
		outtextxy(650, 350, L"利");
	}
}

void drawGame()
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 600);
	setfillcolor(BROWN);
	setcolor(BROWN);
	fillrectangle(50, 50, 550, 550);
	setcolor(BLACK);
	for (i = 0; i < 11; i++)
	{
		line(100, 100 + i * 40, 500, 100 + i * 40);
		line(100 + i * 40, 100, 100 + i * 40, 500);
	}

	for (i = 0; i < 11; i++)
	{
		for (j = 0; j < 11; j++)
		{
			if (map[i][j] == 1)
			{
				setfillcolor(BLACK);
				setcolor(BLACK);
				fillcircle(100 + j * 40, 100 + i * 40, 16);
			}
			if (map[i][j] == 2)
			{
				setfillcolor(WHITE);
				setcolor(WHITE);
				fillcircle(100 + j * 40, 100 + i * 40, 16);
			}
		}
		if (player == PLAYER_1)
		{
			setcolor(BLACK);
		}
		else
		{
			setcolor(WHITE);
		}
		setcolor(BLACK);
		rectangle(82 + cx * 40, 82 + cy * 40, 118 + cx * 40, 118 + cy * 40);
		showPlayer(player);
	}

}
void changePlayer()
{
	if (player == PLAYER_1)
		player = PLAYER_2;
	else
		player = PLAYER_1;

}
void GameControl()
{
	if (isWin == 0 && GetAsyncKeyState(VK_UP) & 0x8000)
	{
		cy--;
		if (cy == -1)cy = 10;
	}
	if (isWin == 0 && GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		cx--;
		if (cx == -1)cx = 10;
	}
	if (isWin == 0 && GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		cy = (cy + 1) % 11;
	}
	if (isWin == 0 && GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		cx = (cx + 1) % 11;
	}
	if (isWin == 0 && GetAsyncKeyState(VK_SPACE) & 0x8000)
	{

		if (map[cy][cx] == 0) 
		{
			map[cy][cx] = player;
			if (judgeWin()) {
				isWin = 1;
			}
			else
				changePlayer();
		}
	}
	if (isWin == 1 && (GetAsyncKeyState(VK_ESCAPE) & 0x8000))
	{
		isWin = 0;
		cx = 5;
		cy = 5;
		initMap();
	}
}

void GameStartUI()
{

}
int main()
{
	printf("你希望黑方先走吗？（输入1确定，2为白棋先走）\n");
	scanf_s("%d", &blackFirst);
	switch (blackFirst)
	{
	case 1:player = PLAYER_1;
		break;
	case 2:player = PLAYER_2;
		break;
	default:printf("Error\n");

	}

	initgraph(800, 600);
	BeginBatchDraw();
	while (1)
	{
		GameStartUI();
		GameControl();
		drawGame();

		FlushBatchDraw();
		Sleep(100);
	}
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
