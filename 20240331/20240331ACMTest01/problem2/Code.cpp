#include <stdio.h>  

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int lcm_of_three(int a, int b, int c) {
    return lcm(lcm(a, b), c);
}

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    if (a < 1 || a >= 30 || b < 1 || b >= 30 || c < 1 || c >= 30) {
        printf("输入错误！请输入小于30的正整数。\n");
        return 1;
    }

    int num = lcm_of_three(a, b, c);

    printf("%d\n", num);

    return 0;
}