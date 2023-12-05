// 精灵旋转.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>

IMAGE bk, r, npc, bw;
int x;
double d = 0;
int frame = 0;
int direction = 1;
int nx = 200;
int ny = 200;
void drawGame()
{

}
void GameControl()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		ny -= 10;
		direction = 3;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		ny += 10;
		direction = 0;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		nx -= 10;
		direction = 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		nx += 10;
		direction = 2;
	}
}
void GameLogic()
{

}

int main()
{
	initgraph(800, 600);
	loadimage(&bk, L"UH]U5D114GLPYW$P]RBNEO2.jpg");
	loadimage(&npc, L"modern-rabbit.png",256,256);
	loadimage(&bw, L"tz.png",256,256);
	BeginBatchDraw();
	while (1)
	{
		x++;
		d += 0.1;
		frame = (frame + 1) % 4;
		rotateimage(&r, &bk, d);
		putimage(0, 0, &r, SRCCOPY);
		putimage(x, 50, 100, 150, &bk, 360, 450, SRCCOPY);
		

		//镂空算法
		
		putimage(200, 200, 64, 64, &npc, 0+frame*64, 0+direction*64, SRCINVERT);
		putimage(200, 200, 64, 64, &bw, 0 + frame * 64, 0 + direction * 64, SRCAND);
		putimage(200, 200, 64, 64, &npc, 0 + frame * 64, 0 + direction * 64, SRCINVERT);
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
