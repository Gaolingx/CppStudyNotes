#include <stdio.h>  


int countTransformations(int n);

int main() {
    int n;
    scanf("%d", &n);

    if (n <= 1) {
        printf("输入错误，n必须大于1。\n");
        return 1;
    }

    int transformations = countTransformations(n);
    printf("%d", transformations);

    return 0;
}

int countTransformations(int n) {
    int count = 0;

    while (n != 1) {
        if (n % 2 == 1) {
            n = 3 * n + 1;
        }
        else {
            n = n / 2;
        }
        count++;
    }

    return count;
}