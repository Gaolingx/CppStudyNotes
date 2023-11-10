﻿#include <graphics.h>
#include <math.h>
short map0[30][30] = {
{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
{ 3, 8, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0,
0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0,
0, 3, 3, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 3, 0, 0,
0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0,
0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0,
0, 0, 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0,
0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0,
0, 0, 3, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0,
0, 0, 3, 3, 0, 0, 0, 0, 3, 3, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 3, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3 },
{ 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3 },
{ 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3 },
{ 3, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3 },
{ 3, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3 },
{ 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3 },
{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3 },
{ 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
3, 3, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3 },
{ 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3 },
{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 3, 3, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3 },
{ 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
0, 3, 3, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 3,
3, 3, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
{ 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 10 }
};
int main()
{
	int i, j;
	int cx, cy;
	cx = 1;
	cy = 1;
	initgraph(600, 600);
	BeginBatchDraw();
	while (1)
	{
		setfillcolor(BLACK);
		fillrectangle(0, 0, 600, 600);
		for (i = max(0, cy - 3); i < min(30, cy + 3); i++)
			for (j = max(0, cx - 3); j < max(0, cx + 3); j++) {
				if (map0[i][j] == 3) {
					setcolor(BROWN);
					setfillcolor(BROWN);
					fillrectangle(0 + j * 20, 0 + i * 20, 20 + j * 20, 20 + i * 20);
				}
				if (map0[i][j] == 10) {
					setcolor(RED);
					setfillcolor(RED);
					fillrectangle(0 + j * 20, 0 + i * 20, 20 + j * 20, 20 + i * 20);
				}
				if (map0[i][j] == 8)
				{
					setcolor(YELLOW);
					setfillcolor(YELLOW);
					fillcircle(10 + j * 20, 10 + i * 20, 9);
				}
			}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (map0[cy + 1][cx] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy + 1][cx] = 8;
				cy++;
			}
			if (map0[cy + 1][cx] == 10)
			{
				map0[cy][cx] = 0;
				map0[1][1] = 8;
				cy = 1;
				cx = 1;
			}
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (map0[cy - 1][cx] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy - 1][cx] = 8;
				cy--;
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
			if (map0[cy][cx + 1] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy][cx + 1] = 8;
				cx++;
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
			if (map0[cy][cx - 1] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy][cx - 1] = 8;
				cx--;
			}
			if (map0[cy + 1][cx] == 10)
			{
				map0[cy][cx] = 0;
				map0[1][1] = 8;
				cy = 1;
				cx = 1;
			}
		}
		FlushBatchDraw();
		Sleep(50);
	}
	EndBatchDraw();
	closegraph();
}