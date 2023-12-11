// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <graphics.h>
#include<stdlib.h>
TCHAR b[10];
struct coin
{
	int cx;
	int cy=-10;
	int vy=0;
	int g=1;
	int d;
	int life=0;
}c[10000];
IMAGE Au, Ag, Cu, Fe, bw,bk;

int px=250;
int py=700;
int count = 0;
void creatcoin() {
	int i;
	for (i = 0; i < 10000; i++) {
		if (c[i].life == 0) {
			c[i].cx = rand() % 560 + 20;
			c[i].life = 1;
			c[i].d = rand() % 4;
			break;
		}
	}
}
void movecoin() {
	int i;
	for (i = 0; i < 10000; i++) {
		if (c[i].life == 1) {
			c[i].cy += c[i].vy;
			c[i].vy += c[i].g;

		}
	}
}
void drawgame() {

	setfillcolor(BLACK);
	fillrectangle(0, 0, 600, 800);
	loadimage(&bk, L"bk.jpg",600,800);
	putimage(0, 0, &bk,SRCCOPY);
	loadimage(&Au, L"Au.png", 40, 40);
	loadimage(&Ag, L"Ag.png", 40, 40);
	loadimage(&Cu, L"Cu.png", 40, 40);
	loadimage(&Fe, L"Fe.png", 40, 40);
	loadimage(&bw, L"bw2.png", 40, 40);
	for (int i = 0; i < 10000; i++) {
		if (c[i].life == 1&&c[i].d==1) {
			putimage(c[i].cx, c[i].cy, &Au, SRCINVERT);
			putimage(c[i].cx, c[i].cy, &bw, SRCAND);
			putimage(c[i].cx, c[i].cy, &Au, SRCINVERT);
		}
		if (c[i].life == 1 && c[i].d == 2) {
			putimage(c[i].cx, c[i].cy, &Ag, SRCINVERT);
			putimage(c[i].cx, c[i].cy, &bw, SRCAND);
			putimage(c[i].cx, c[i].cy, &Ag, SRCINVERT);
		}
		if (c[i].life == 1 && c[i].d == 3) {
			putimage(c[i].cx, c[i].cy, &Cu, SRCINVERT);
			putimage(c[i].cx, c[i].cy, &bw, SRCAND);
			putimage(c[i].cx, c[i].cy, &Cu, SRCINVERT);
		}
		if (c[i].life == 1 && c[i].d == 4) {
			putimage(c[i].cx, c[i].cy, &Fe, SRCINVERT);
			putimage(c[i].cx, c[i].cy, &bw, SRCAND);
			putimage(c[i].cx, c[i].cy, &Fe, SRCINVERT);
		}
	}
	setcolor(GREEN);
	setfillcolor(GREEN);
	fillrectangle(px,py, px+100, py + 40);

	wsprintf(b, L"得分%d", count);
	outtextxy(50, 400, b);
}
void ctrl() {
	if (GetAsyncKeyState('A') & 0x8000) {
		px -=20;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		px += 20;
	}
}
void scorecoin()
{
	int i = 0;
	if (c[i].cy > 400 && c[i].cx > px)
	{
		count++;
	}
}
void gamelogic() {
	creatcoin();
	movecoin();
	scorecoin();
}
int main()
{
	initgraph(600, 800);
	BeginBatchDraw(); 
	
	while (1)
	{
		drawgame();
		ctrl();
		gamelogic();


		FlushBatchDraw();
		Sleep(30);
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
