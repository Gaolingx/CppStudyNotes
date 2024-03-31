#include <stdio.h>  
#include <math.h>  

int main() {
    double number;
    scanf("%lf", &number);

    double absolute_value = fabs(number);
    printf("%.2f\n", absolute_value);

    return 0;
}