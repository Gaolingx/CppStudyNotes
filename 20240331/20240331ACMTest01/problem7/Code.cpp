#include<stdio.h>
#include<string.h>
void put(int n)
{
	if (n == 1)
	{
		printf("%c", 'A');
	}
	else
	{
		put(n - 1);
		printf("%c", 'A' + n - 1);
		put(n - 1);
	}
}
int main()
{
	int a = 0;
	scanf("%d", &a);
	put(a);
}