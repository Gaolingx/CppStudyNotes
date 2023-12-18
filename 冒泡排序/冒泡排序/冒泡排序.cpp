﻿// 冒泡排序.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include "time.h"
#include "stdlib.h"

int main()
{
    int a[10], i, j, temp;
    srand(time(NULL));
    for (i = 0; i < 10; i++)
    {
        a[i] = rand() % 100;  //用for循环生成一个包含10个随机整数的数组，每个整数的范围是0到99。
    }
    //外循环决定冒泡循环次数，因为每次冒泡操作都会将一个最大的数移到数组的末尾，所以最多需要进行9次冒泡操作。
    for (i = 1; i < 10; i++)
    {   
        //内循环，用于比较和交换元素。因为每次外循环后，最大的数都会移到数组的末尾，所以内循环每次可以少遍历一个元素。
        for (j = 0; j < 10 - i; j++)
        {
            //比较和交换操作
            if (a[j] < a[j + 1])  //比较当前元素和下一个元素的大小。如果当前元素小于下一个元素，则交换它们的位置。
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                // 交换两个元素的位置。这是通过三个步骤完成的：
                // 先将temp赋值为a[j]，然后将a[j + 1]的值赋给a[j]，
                // 最后将temp（即原来的a[j]）赋给a[j + 1]。这样，两个元素的位置就被交换了。
            }
        }
    }
    for (i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
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
