// cjjtest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <graphics.h>
#include <conio.h>
#include <time.h>
#include<iostream>
#include "windows.h"
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")
IMAGE image;


#define WIDTH 30  // 迷宫宽度
#define HEIGHT 30  // 迷宫高度
#define WALL_SIZE 30  // 墙的尺寸
#define PATH_COLOR RGB(216, 216, 216)
#define WALL_COLOR RGB(80, 80, 80)
#define PLAYER_COLOR RGB(0, 255, 0)
#define EXIT_COLOR RGB(255, 0, 0)

int maze[HEIGHT][WIDTH];  // 存储迷宫的二维数组
int player_x, player_y;   // 玩家所在位置的坐标
int exit_x, exit_y;       // 出口所在位置的坐标





// 绘制单元格
void draw_cell(int x, int y, int type) {
    switch (type) {
    case 0:
        setfillcolor(PATH_COLOR);   // 路
        break;
    case 1:
        setfillcolor(WALL_COLOR);   // 墙
        break;
    case 2:
        setfillcolor(PLAYER_COLOR); // 玩家
        break;
    case 3:
        setfillcolor(EXIT_COLOR);   // 出口
        break;
    default:
        break;
    }
    solidrectangle(x * WALL_SIZE, y * WALL_SIZE, (x + 1) * WALL_SIZE, (y + 1) * WALL_SIZE);
}

// 绘制迷宫
void draw_maze() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            draw_cell(j, i, maze[i][j]);
        }
    }
}

// 生成迷宫                
void generate_maze() {
    // 初始化迷宫
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                maze[i][j] = 1;  // 迷宫边缘固定为墙
            }
            else {
                maze[i][j] = 0;  // 其余位置初始化为空路
            }
        }
    }



    // 随机生成迷宫的内部结构
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDTH - 1; j++) {
            if (rand() % 100 < 30) {
                maze[i][j] = 1;
            }
        }
    }

    // 随机生成入口和出口
    player_y = rand() % (HEIGHT - 2) + 1;
    maze[player_y][0] = 2;

    exit_y = rand() % (HEIGHT - 2) + 1;
    maze[exit_y][WIDTH - 1] = 3;

    // 防止入口和出口重叠
    while (exit_y == player_y) {
        exit_y = rand() % (HEIGHT - 2) + 1;
    }
}

// 移动玩家
void move_player(int x, int y) {
    if (maze[y][x] != 1) {
        maze[player_y][player_x] = 0;
        player_x = x;
        player_y = y;
        maze[player_y][player_x] = 2;
    }
}

// 检查是否到达出口
bool check_exit(int x, int y) {
    if (x == WIDTH - 1 && y == exit_y) {
        return true;
    }
    else {
        return false;
    }
}

void controlGame()
{
    if (_kbhit()) {  // 判断是否有键盘输入
        char input = _getch();

        switch (input) {
        case 'w':
            move_player(player_x, player_y - 1);
            break;
        case 's':
            move_player(player_x, player_y + 1);
            break;
        case 'a':
            move_player(player_x - 1, player_y);
            break;
        case 'd':
            move_player(player_x + 1, player_y);
            break;
        default:
            break;
        }
    }
}
int main()
{
    PlaySound(L"bgm.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    loadimage(&image, L"1.jpg", 400);
    initgraph(WIDTH * WALL_SIZE, HEIGHT * WALL_SIZE);
    generate_maze();

    while (1)
    {
        draw_maze();
        controlGame();

        if (check_exit(player_x, player_y))
        {
            break;
        }

        Sleep(5);  // 延时

        if (player_x == 23 && player_y == 9)
        {
            putimage(0, 0, &image, SRCCOPY);
        }
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
