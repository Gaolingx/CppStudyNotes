/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_MEMBERS 10

int main() {
    int numMembers, i;
    char memberNames[MAX_MEMBERS][50];
    int leaderIndex;

    // ��ʾ�û�����С���Ա����
    printf("������С���Ա���������%d�ˣ���", MAX_MEMBERS);
    scanf("%d", &numMembers);

    // ��ʾ�û���������ÿ����Ա������
    printf("����������ÿ����Ա��������\n");
    for (i = 0; i < numMembers; i++) {
        printf("��Ա%d��������", i + 1);
        scanf("%s", memberNames[i]);
    }

    // ���ݵ�ǰʱ���������������
    srand(time(0));

    // �������������ʾѡ�е�С�鳤����
    leaderIndex = rand() % numMembers;

    // ���ѡ�е�С�鳤
    printf("ѡ�е�С�鳤�ǣ�%s\n", memberNames[leaderIndex]);

    return 0;
}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char name[50];
    int isLeader;
} Member;

void selectLeader(Member* members, int numMembers) {
    // �������������
    srand(time(0));

    // ���ѡȡС�鳤
    int leaderIndex = rand() % numMembers;

    // ����С���Ա��С�鳤����
    for (int i = 0; i < numMembers; i++) {
        if (i == leaderIndex) {
            members[i].isLeader = 1;
        }
        else {
            members[i].isLeader = 0;
        }
    }
}

int main() {
    int numMembers;

    printf("������С���Ա������");
    scanf("%d", &numMembers);

    // ��̬�����Ա������ڴ�
    Member* members = (Member*)malloc(numMembers * sizeof(Member));

    // ����С���Ա����
    for (int i = 0; i < numMembers; i++) {
        printf("������� %d ����Ա��������", i + 1);
        scanf("%s", members[i].name);
    }

    // ѡȡС�鳤
    selectLeader(members, numMembers);

    // ������
    printf("\nС���Ա�����ɫ��\n");
    for (int i = 0; i < numMembers; i++) {
        printf("%s\t%s\n", members[i].name, members[i].isLeader ? "С�鳤" : "��Ա");
    }

    // �ͷ��ڴ�
    free(members);

    return 0;
}
*/

/*
#include <stdio.h>
void main()
{
    int n;
    scanf_s("%d", &n);
    switch (n)
    {
    case 0:printf("Sunday\n");
        break;
    case 1:printf("Monday\n");
        break;
    case 2:printf("Tuesday\n");
        break;
    case 3:printf("Wednesday\n");
        break;
    case 4:printf("Thursday\n");
        break;
    case 5:printf("Friday\n");
        break;
    default:printf("Error");
    }
}
*/

/*
#include "stdio.h"
void main()
{float x,y;
int n;
scanf("%f",&x);
n=(int)x/10;
if((int)x/10==x/10) n--;
switch(n)
{case 0:y=x*0.1;break;
case 1:y=x*0.12;break;
case 2:case 3:y=x*0.14;break;
case 4:case 5:y=x*0.16;break;
case 6:case 7:case 8:case 9:y=x*0.18;break;
default:y=x*0.2;
}
printf("y=%.2f\n",y);
}

*/
/*
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
void main()  //�иĶ� 
{
    int year, month, day, sum, flag;
    printf("%�����������գ�");
    scanf("%d %d %d", &year, &month, &day);
    switch (month)       //�иĶ� 
    {
    case 1:sum = 0; break;
    case 2:sum = 31; break;
    case 3:sum = 59; break;
    case 4:sum = 90; break;
    case 5:sum = 120; break;
    case 6:sum = 151; break;
    case 7:sum = 181; break;
    case 8:sum = 212; break;
    case 9:sum = 243; break;
    case 10:sum = 273; break;
    case 11:sum = 304; break;
    case 12:sum = 334; break;
    default:printf(" error\n"); break;
    }
    sum = sum + day;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        flag = 1;
    else
        flag = 0;
    if (flag == 1 && month > 2)  //�иĶ�
        sum = sum + 1;
    printf("%d\n", sum);
}
*/

/*
#include <stdio.h>

void main()
{
    char ch;
    int num = 0;
    ch = getchar();
    do
    {
        num++;
        ch = getchar();
    }     while  (ch  !=  '\n');
    printf("num = % d\n", num);
 }*/

/*
#include<stdio.h>
void main()
 {
     long int k, s;
     s = 0;
     for (k = 1; k <= 1000; k++)
         s = s + k;
     printf("s=%ld", s);
 }*/

/*
#include<stdio.h>
#include <corecrt_math.h>

void main()
{
    int x, k;
    scanf_s("%d", &x);
    for (k = 2; k <= sqrt(x); k++)
        if (x % k == 0)
            break;

    if (k > sqrt(x))
        printf("%d is a prime", x);
    else
        printf("%d is not a prime", x);
}
*/
/*
#include<stdio.h>

void main() 
{
    int x, a, b, c, num = 0;

    for (x = 100; x <= 999; x++) {
        a = x / 100; b = x / 10 % 10; c = x % 10;
        if (a != b && a != c && b!=c)
        {
            num++;
            printf("%5d", x);
        }
    }
    printf("\nnumber=%d", num);
}
*/
/*
#include <stdio.h>

void main()
{
    long f1 = 1,f2 = 1,f3;
int k;
printf("%ld\t%ld\t", f1,f2);

for (k = 3; k <= 30; k++)
{
    f3 = f1 + f2;
    printf("%ld\t", f3);
    f1 = f2; f2 = f3;
}
}
*/
/*
#include<stdio.h>
void main()
{
    int x, k;
    for (x = 300; x >= 1; x--)
        if (x % 17 == 0)
            break;
    printf("x=%d\n", x);
}
*/
/*
#include <stdio.h>

int main()
{
    int n, i, j;
    scanf_s("%d", &n);
    for (i = 1; i <= n; i++)
    {
            for (j = 0; j < n - i; j++)
                printf(" ");
            for (j = 0; j < 2 * i - 1; j++)
                printf("*");

        printf("\n");
    }

    for (i = 1; i <= n - 1; i++)
    {
        for (j = 1; j <= i; j++)
        {
            printf(" ");
        }

        for (j = 0; j < 2 * (n-i)-1; j++)
            printf("*");

        printf("\n");
    }
}
*/
/*
#include <iostream>

using namespace std;

int main() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            cout << j << "*" << i << "=" << i * j << " ";
        }
        cout << endl;
    }
    return 0;
}
*/
/*
#include <stdio.h>

void main()
{
     float s = 0, f1 = 2, f2 = 1, f = 1, t, n;
     for (n = 1; n <= 10; n++)
     {
         s = s + f * f1 / f2;
         f = f * (-1); t = f2; f2 = f1; f1 = f1 + t;
     }
     printf("s=%f\n", s);
}
*/
/*
#include<stdio.h>
void main()
{
    long y, n;
    scanf_s("%ld", &y);
    while (y != 0)
    {
        n = y % 10;
        printf("%ld", n);
        y = y / 10;
    }
}
*/
/*
#include<stdio.h>
void main()
{
    int x = 1, n;
    for (n = 4; n > 1; n--)
        x = (x + 1) * 2;
    printf("%d", x);
}
*/
/*
#include<stdio.h>
    void main() 
    {
        int i, j, k;  //iС����jĸ����k����
        for(i = 3;i<=99;i+=3)
        for (j = 3; j <= 33; j++)
        {
            k = 100 - i - j;
            if (k > 0 && i / 3 + 3 * j + k * 5 == 100)
            {
                printf("%d %d %d\n", i, j, k);
            }
        }
    }
*/
/*
#include<graphics.h>
#include<stdio.h>

int main()
{
    int i;
    initgraph(800, 600);
    while (1)
    {
        setfillcolor(BROWN);
        fillrectangle(30, 30, 540, 540);
        setcolor(BLACK);
        for (i = 0; i < 15; i++)
        {
            line(75, 75 + i * 30, 495, 75 + i * 30);
            line(75 + i * 30, 75, 75 + i * 30, 495);
        }
        FlushBatchDraw();
    }
    EndBatchDraw();
    closegraph();
}
*/
/*
#include<stdio.h>
#include"math.h"

	void main()
	{
		int a = 3, b = 4;
		printf("%d\n", (a = b, b, a + 3)); 
		printf("%d\n", a = b, b, a + 3);
	}
    */
    /*
    ��C�����У������������һ���ǳ���Ҫ��������������մ����ҵ�˳�����ÿ�����ʽ�����������һ�����ʽ��ֵ��
        ��������������������䣺

        printf("%d\n", (a = b, b, a + 3));
    printf("%d\n", a = b, b, a + 3);

    �ڵ�һ������У�ʹ�������ţ�ʹ�ö�������������ȼ����ڸ�ֵ���������ˣ����ʽ(a = b, b, a + 3) ���ȱ����㡣
        * ���ȣ�`a = b` ִ�У��� `b` ��ֵ���� `a`�� * Ȼ��`b` �����㲢���ء� * ���`a + 3` �����㲢���ء���ˣ��������ʽ��ֵ�� `a + 3`��

        ���ڵڶ�������У�û��ʹ�����ţ����Ը�ֵ����� = �����ȼ����ڶ������������ˣ�a = b ������ִ�У�Ȼ�� b �� a + 3 �ᱻ���㲢���ء����� a = b �Ѿ��� b ��ֵ������ a�����Եڶ����������ֵӦ�����һ�������ͬ��
        ���ԣ���� a �� b �ĳ�ʼֵ��һ���ģ���ô�������������Ӧ����һ���ġ�������ǵ�ֵ��ͬ����ô�ڶ�������������ܻ᲻ͬ�ڵ�һ����䡣
     */
/*
#include<stdio.h>

int main()
{
    int a[2000], i, j, n;
    scanf_s("%d", &n);
    for (i = 0; i < n; i++)
    {
        a[i] = 1;
    }
    for (i = 0, j = 0; i < (n-1)*3;)
    {
        if (a[j] != 0)
        {
            i++;
            if (i % 3 == 0)a[j] = 0;
        }
        j = (j + 1) % n;
    }
    for (i = 0; i < n; i++)
    {
        if (a[i] == 1)
        {
            printf("%d", i + 1);
        }
    }
}
*/
/*
#include<stdio.h>

void main()
{
    long x; int i, j, n, d[20];
    scanf_s("%ld", &x);
    n = 0;
    do
    {
        d[n] = x % 10; x = x / 10; n++;
    } while (x != 0);
    for (i = 0, j = n - 1; i < j; i++, j--)
        if (d[i] != d[j])
            break;
    if (i < j)
        printf("NOT");
    else
        printf("YES");
}
*/
/*
#include<stdio.h>

void main()
{
    int i, j, a[3][4];
    printf("input array numbers:\n");
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            scanf_s("%d", &a[i][j]);
    printf("output array numbers\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
            printf("%d", a[i][j]);
        printf("\n");
    }
}
*/
/*
#include <stdio.h>
#include <conio.h>

void main()
{
    char s[20]; int odd = 1, even = 1; int i;
    
    printf("Enter a number: ");
    gets_s(s);
    i = 0;
    while (s[i] != '\0')
    {
        if ((s[i] - 48) % 2 == 0)
            odd = 0;
        else
            even = 0;
        i++;
    }
    if (odd == 1 || even == 1)
        printf("YES!");
    else
        printf("NO!");
}
*/
/*
#include <stdio.h>
#include "time.h"
#include "stdlib.h"

int main()
{
    int a[10], i, j, temp;
    srand(time(NULL));
    for (i = 0; i < 10; i++)
    {
        a[i] = rand() % 100;
    }
    //��ѭ������ð��ѭ������
    for (i = 1; i < 10; i++)
    {
        for (j = 0; j < 10 - i; j++)
        {
            if (a[j] < a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
}
*/
/*
#include <stdio.h>

#define N 10

void main()
{
    int i, j; int x[N][N];
    for(i=0;i<N;i++)
        for (j = 0; j <= i; j++)
        {
            if (j == 0 || i == j)
                x[i][j] = 1;
            else
                x[i][j] = x[i - 1][j] + x[i - 1][j - 1];

        }
    for (i = 0; i < N; i++)
    {
        for (j = 0; j <= i; j++)
            printf("%d", x[i][j]);
        printf("\n");
    }
}
*/
#include <stdio.h>
#include "time.h"
#include "stdlib.h"


int main()
{
    int a[54];
    int b[18];
    int c[18];
    int d[18];

    int i;
    int t1, t2, temp;
    for (i = 0; i < 54; i++)
    {
        a[i] = i;
    }
    for (i = 0; i < 10000; i++)
    {
        t1 = rand() % 54;
        t2 = rand() % 54;
        temp = a[t1];
        a[t1] = a[t2];
        a[t2] = temp;
    }
    for (i = 0; i < 18; i++)
    {
        b[i] = a[i];
        c[i] = a[i + 18];
        d[i] = a[i + 36];
    }
    for (i = 0; i < 18; i++)
    {
        printf("%d", b[i]);
    }
    printf("\n");
    for (i = 0; i < 18; i++)
    {
        printf("%d ", c[i]);
    }
}