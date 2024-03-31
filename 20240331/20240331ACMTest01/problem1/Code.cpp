#include <stdio.h>
#include <stdlib.h>
 
int  CompactIntegers(int *a,int n);
 
int main()
{
    int s,i,a[100],n;
    scanf("%d",&n);
    for (i=0; i<n; i++)
    {
        scanf("%d",&a[i]);
    }
    s=CompactIntegers(a,n);
    for (i=0; i<s; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n%d",s);
    return 0;
}
 
int  CompactIntegers(int *a,int n)
{
    int i,cnt=0;
    for (i=0; i<n; i++)
    {
        if (a[i]!=0)
        {
            a[cnt++]=a[i];
        }
    }
    return cnt;
}