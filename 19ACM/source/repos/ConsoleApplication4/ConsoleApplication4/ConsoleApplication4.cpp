// ConsoleApplication4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main()
{
	int length;
	int arr[20] = { 0 };
	int i, j;
	int a = 0;
	scanf("%d", &length);
	for (i = 0; i < length; i++)
	{
		printf("", ++a);
		scanf("%d", &arr[i]);
	}
	int max = arr[0];
	for (j = 0; j < length; j++)
	{
		if (max < arr[j])
		{
			max = arr[j];
		}
	}
	printf("%d\n", max);
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
