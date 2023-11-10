// ConsoleApplication3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <graphics.h>
#include "stdlib.h"
#include "math.h"
#define  STATE_BAI 0
#define  STATE_SHEN 1
#define  STATE_LA 2
int main()
{
	int cx, cy;
	int lx, ly;
	int vx, vy, g;
	int state = STATE_BAI;
	float lineLength = 150.0;
	double dd = 0;
	double vd = 0.1;
	cx = 50;
	cy = 30;
	vx = 10;
	vy = 0;
	g = 1;
	lx = 400;
	ly = 300;
	initgraph(800, 600);
	while (1)
	{
		/*setcolor(BLACK);
		circle(cx, cy, 10);*/
		/*cx += vx;
		cy += vy;
		vy += g;
		if (cy + 10 >= 600)vy *= -0.7;*/
		/*if (cx + 10 <= 0 || cx + 10 >= 800)vx *= -1;
		if (cy + 10 <= 0 || cy + 10 >= 600)vy *= -1;*/
		/*setcolor(RGB(rand()%256, rand() % 256, rand() % 256));
		circle(cx, cy, 10);*/

		setcolor(BLACK);
		line(400, 100, lx, ly);
		switch (state)
		{
		case STATE_BAI:
			dd += vd;
			if (dd > 1.5 || dd < -1.5)vd *= -1;
			break;
		case STATE_SHEN:
			lineLength += 10;
			if (lineLength > 400)
			{
				state = STATE_LA;
			}
			break;
		case STATE_LA:
			lineLength -= 10;
			if (lineLength <= 150) {
				lineLength = 150;
				state = STATE_BAI;
			}
			break;
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (state == STATE_BAI) {
				state = STATE_SHEN;
			}
		}
		lx = 400 + lineLength * sin(dd);
		ly = 100 + lineLength * cos(dd);

		setcolor(YELLOW);
		line(400, 100, lx, ly);



		Sleep(50);
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
