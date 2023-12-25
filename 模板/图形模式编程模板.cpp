#include <stdio.h>
#include "graphics.h"
#include <stdlib.h>
#include <time.h>

void loadRes()
{

}

void Init()
{
	initgraph(800, 600);
}

void drawGame()
{

}

void GameControl()
{

}

void GameLogic()
{

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