// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main()
{		
	int Speed = 100;
	int foodSize = 10;
	int snakeX[1000];
	int snakeY[1000];
	int direction = 0;
	int foodX, foodY;
	int count = 2;
	int i;
	snakeX[0] = 100;
	snakeY[0] = 100;
	snakeX[1] = 100;
	snakeY[1] = 110;
	foodX = rand() % 80 * 10;
	foodY = rand() % 60 * 10;

	printf("请输入蛇蛇的速度：", Speed);
	scanf_s("%d", &Speed);
	printf("请输入蛇蛇的大小：", foodSize);
	scanf_s("%d", &foodSize);

	initgraph(800, 600);
	BeginBatchDraw();


	while (1)
	{
		setfillcolor(BLACK);
		fillrectangle(0, 0, 800, 600);
		setfillcolor(YELLOW);
		fillrectangle(foodX, foodY, foodX + foodSize, foodY + foodSize);

		for (i = 0; i < count; i++)
		{
			setfillcolor(RED);
			fillrectangle(snakeX[i], snakeY[i], snakeX[i] + foodSize, snakeY[i] + foodSize);
		}
		//🐍身的移动
		for (i = count - 1; i > 0; i--)
		{
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		//🐍头的移动
		switch (direction)
		{
		case 0:
			snakeY[0] -= 10;
			if (snakeY[0] < 0)snakeY[0] = 600;
			break;

		case 1:
			snakeY[0] += 10;
			if (snakeY[0] > 600)snakeY[0] = 0;
			break;
		case 2:
			snakeX[0] -= 10;
			if (snakeX[0] < 0)snakeX[0] = 800;
			break;
		case 3:
			snakeX[0] += 10;
			if (snakeX[0] > 800)snakeX[0] = 0;
			break;
		}
		//🐍吃东西
		if (sqrt((foodX - snakeX[0])*(foodX-snakeX[0])+(foodY - snakeY[0])*(foodY - snakeY[0])) < 5)
		{
			snakeX[count] = -100;
			snakeY[count] = -100;
			count++;
			foodX = rand() % 80 * 10;
			foodY = rand() % 60 * 10;
		}
		if (count >= 5)
		{
			for (i = 5; i < count; i++)
			{
				if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
				{
					closegraph();
					printf("你死了!");
					Sleep(1000);
					exit(0);
				}
			}
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (direction != 1)direction = 0;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (direction != 0)direction = 1;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			if (direction != 3)direction = 2;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			if (direction != 2)direction = 3;
		}

		FlushBatchDraw();
		Sleep(Speed);

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
