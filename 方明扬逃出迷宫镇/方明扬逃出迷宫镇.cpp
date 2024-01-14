#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include"math.h"
#include"time.h"
#include"fmytcmgz.h"//�Թ���ͼ��ͷ�ļ�
#include<iostream>//��������
#include "windows.h"//��������
#include "mmsystem.h"//��������
#pragma comment(lib,"winmm.lib")
#define STATE_ABOUT 1
#define STATE_LOADING 2
#define STATE_GAME 3
#define STATE_MENU 4
#define WALL_COLOR RGB(80, 80, 80)
#define EXIT_COLOR RGB(255, 0, 0)
IMAGE bk, bk2;
IMAGE dt, rm;
IMAGE fmy,fmyblack;
IMAGE ys,ysblack;
IMAGE bj,klt ;
TCHAR c[3][100];
int state = STATE_GAME;
short(*map)[25];
int j, i, flag = 0;
int lx = 200;
int cx, cy;
int x = 1, y = 1;
int nx = 1, ny = 1, direction = 1;
int zx = 740, zy = 730;//Կ��λ��
void drawGame()        
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, 800, 800);
	switch (state)
	{
	case STATE_MENU:
		setbkmode(TRANSPARENT);
		putimage(0, 0, 1000, 900, &bk, 0, 0, SRCCOPY);
		setcolor(BLACK);
		settextstyle(50, 0, L"����");//�����С��������ɫ������
		outtextxy(380, 220, L"�������ӳ��Թ���");//���ֵ�X��Y���� 
		settextstyle(45, 0, L"����");//�������������С��������		
		for (i = 0; i < 3; i++)
		{
			outtextxy(330, 250 + i * 45, c[i]);
		}
		setfillcolor(WHITE);
		fillrectangle(540, 280 + flag * 90, 750, 350 + flag * 90);
		outtextxy(550, 300, L"��ʼ��Ϸ");
		outtextxy(550, 390, L"��Ϸ����");
		outtextxy(550, 480, L"�˳���Ϸ");
		break;
	case STATE_ABOUT:
		//��Ϸ����ҳ�����
		setcolor(WHITE);
		setbkmode(TRANSPARENT);//ʹ�������ڱ�������
		putimage(0, 0, 1000, 900, &bj, 0, 0, SRCCOPY);
		settextstyle(33, 0, L"����");
		outtextxy(50, 50, L"������ܣ�");
		outtextxy(90, 100, L"���۾��˷���������;�����������ص��Թ���");
		outtextxy(50, 150, L"���ϵ�������ɫ���صظ����������Թ�����˴�");
		outtextxy(50, 200, L"��û�г�ȥ�����������˴��룬��Ҫͨ��С���");
		outtextxy(50, 250, L"�ϵ��Թ����ҵ��Թ��е�����Կ�ף��⿪�Թ���");
		outtextxy(50, 300, L"�ķ�ӡ�����ܽ⿪���䡢��С���ػ����ɡ�����");
		outtextxy(50, 350, L"�Թ����еĶ�����ʹ��������屣��һ�����ƣ�");
		outtextxy(50, 400, L"��ֻ�������ֽ�Ӳ������ǰ������������Կ�״�");
		outtextxy(50, 450, L"�����������ǻۡ����飬��Ѱ��Կ�׵Ĺ����У�");
		outtextxy(50, 500, L"��������������ЩƷ�ʵ����С����ύ��");
		outtextxy(50, 550, L"�Թ���ĺ����˷������������ǿ˷��������ѣ�");
		outtextxy(50, 600, L"�����ҵ�������Կ�ף��������ｫ����Կ�ײ�");
		outtextxy(50, 650, L"���ӡ֮�ص�ʯ��ʱ��һ��ҫ�۵Ĺ�â����");
		outtextxy(50, 700, L"С������䱻�⿪�������ػ�������");
		outtextxy(90, 750, L" �����������������;��̽���Ҵ����й�!");
		break;
	case STATE_LOADING:
		putimage(0, 0, 1000, 900, &bk2, 0, 0, SRCCOPY);
		setcolor(WHITE);
		settextstyle(50, 0, L"����");
		outtextxy(100, 250, L"���ڽ����Թ������Ե�...");
		//���ƽ�����
		setcolor(BLACK);
		rectangle(150, 450, 650, 480);
		setcolor(WHITE);
		setfillcolor(WHITE);
		fillrectangle(151, 451, lx, 479);
		break;
	case STATE_GAME:
		//��ʾ��ͼ		
		map = map0;		
		setfillcolor(WHITE);
		fillrectangle(0, 0, 800, 800);
		for (i = max(0, cy - 3); i < min(30, cy + 3); i++)
			for (j = max(0, cx - 3); j < max(0, cx + 3); j++) {
				if (map[i][j] == 8)
				{
					//putimage(0, 0, 1000, 900, &klt, 0, 0, SRCCOPY);
					//fmy appear���ڰ�͸����ͼƬ�����ã�
					putimage(nx + 35, ny + 35, 25, 25, &fmy, 0, 0, SRCINVERT);
					putimage(nx + 35, ny + 35, 25, 25, &fmyblack, 0, 0, SRCAND);
					putimage(nx + 35, ny + 35, 25, 25, &fmy, 0, 0, SRCINVERT);
					//ys appear
					putimage(zx, zy, 35, 35, &ys, 0, 0, SRCINVERT);
					putimage(zx, zy, 35, 35, &ysblack, 0, 0, SRCAND);
					putimage(zx, zy, 35, 35, &ys, 0, 0, SRCINVERT);

				}
				else if (map[i][j] != 0)
				{
					putimage(0 + j * 32, 0 + i * 32, 32, 32, &dt, (map[i][j]+10) % 8 * 32, (int)((map[i][j]+10) / 6) * 32, SRCCOPY);
				}
			}
	}
}
void ctrlGame()
{
	switch (state)
	{
	case STATE_MENU:
		//����ļ��̿���
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			flag--;
			if (flag == -1)flag = 2;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			flag = (flag + 1) % 3;
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (flag == 0)state = STATE_LOADING;
			else if (flag == 1)state = STATE_ABOUT;
			else exit(0);
		}
		break;
	case STATE_ABOUT:
		//�ɽ����л�����Ϸ
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			state = STATE_MENU;
		}
		break;
	case STATE_GAME://���Ʒ������ƶ�(ǽ���޷��赲�����
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			/*
			if (map[y][x - 1]!= 0)//nx - 1 >= 0 && 
			{
				ny -= 10;//���������н��ٶ�
				direction = 3;
			}
			*/
			if (map0[cy - 1][cx] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy - 1][cx] = 8;
				cy--;
				ny -= 32;
			}
			if (map0[cy + 1][cx] == 10)
			{
				map0[cy][cx] = 0;
				map0[1][1] = 8;
				cy = 1;
				cx = 1;
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			/*
			if (map[y][x + 1]== 0)// nx + 1 <= 49 &&
			{
			ny += 10;
			direction = 0;
			}
			*/
			if (map0[cy + 1][cx] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy + 1][cx] = 8;
				cy++;
				ny += 32;
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
			/*
			if (map[y - 1][x] != 0)//ny - 1 >= 0 && 
			{
				nx -= 10;
				direction = 1;
			}
			*/
			if (map0[cy][cx - 1] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy][cx - 1] = 8;
				cx--;
				nx -= 32;

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
			/*
			if (map[y + 1][x] ==0)// ny + 1 <= 49 &&
			{
				nx += 10;
				direction = 2;
			}
			*/
			if (map0[cy][cx + 1] == 0)
			{
				map0[cy][cx] = 0;
				map0[cy][cx + 1] = 8;
				cx++;
				nx += 32;

			}
			if (map0[cy + 1][cx] == 10)
			{
				map0[cy][cx] = 0;
				map0[1][1] = 8;
				cy = 1;
				cx = 1;
			}
		}
		
	}
}
void gameLogic()
{
	//�������ƶ�
	switch (state)
	{
	case STATE_LOADING:
		lx += 15;
		if (lx >= 650)
		{
			state = STATE_GAME;
		}
		break;
	}
}
void drawfmy(IMAGE fmy)
{
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			if (map0[i][j] != 0)
			{
				putimage(0 + j * 16, 0 + i * 16, &fmy, SRCCOPY);
			}
		}	
}
int main()
{
	//PlaySound(L"����Բ - The Chinese Zither.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	initgraph(800, 800);
	loadimage(&bk, L"��Ϸ����2.jpg", 1000, 900);
	loadimage(&dt, L"TEST2.BMP", 512, 1000);//�Թ���ͼͼƬ
	loadimage(&bk2, L"����.png");
	loadimage(&fmy, L"������2.0.png", 27, 27);
	loadimage(&fmyblack, L"������ڰ�ͼ.png", 25, 25);
	loadimage(&ys, L"Կ��.png", 30, 30);//��������ֵ���ͼƬ��С
	loadimage(&ysblack, L"Կ�׺ڰ�ͼ.png", 30, 30);
	loadimage(&bj, L"����2.png",1000, 900);
	loadimage(&klt, L"����ͷ.jpg", 1000, 900);
	BeginBatchDraw();
	cx = 1;
	cy = 1;
	map = map1;
	while (1)
	{
		drawGame();
		ctrlGame();
		gameLogic();
		FlushBatchDraw();
		Sleep(125);
	}
	EndBatchDraw();
	closegraph();
}
