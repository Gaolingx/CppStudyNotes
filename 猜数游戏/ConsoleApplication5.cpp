// ConsoleApplication5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include "stdlib.h"
#include "time.h"
#include "math.h"
int main()
{
	int answer[4], guess, i, j, temp, times = 0;
	int a = 0, b = 0;
	srand(time(NULL));
	for (i = 0; i < 4;) {
		int flag = 0;
		temp = rand() % 10;
		if (i == 0 && temp != 0) {
			answer[i] = temp;
			i++;
		}
		else {
			for (j = 0; j < i; j++) {

				if (answer[j] == temp) { flag = 1; break; }
			}
			if (flag == 0) {
				answer[i] = temp;
				i++;
			}
		}
	}
	while (a != 4)
	{
		a = 0;
		b = 0;
		times++;
		scanf_s("%d", &guess);
		for (i = 3; i >= 0; i--) {
			for (j = 0; j < 4; j++) {
				if ((int)(guess / pow(10, i)) == answer[j]) {
					if (i + j == 3)a++;
					else b++;
				}
			}
			//guess = guess % (int)pow(10, i);

			guess = guess-(int)(guess / pow(10, i))*pow(10, i);
		}
		printf("%d: %dA %dB\n", times, a, b);

	}
	for (i = 0; i < 4; i++) {
		printf("%d ", answer[i]);
	}
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
