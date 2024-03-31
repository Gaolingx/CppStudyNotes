#include <stdio.h>  
#include <string.h>  

int main() {
    char str[1000];
    int max_zeros = 0, max_ones = 0;
    int current_zeros = 0, current_ones = 0;
    int prev_char = -1; 

    scanf("%s", str);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '0') {
            if (prev_char == '1') { 
                current_zeros = 1;
            }
            else {
                current_zeros++;
            }
            if (current_zeros > max_zeros) {
                max_zeros = current_zeros;
            }
        }
        else if (str[i] == '1') {
            if (prev_char == '0') {
                current_ones = 1;
            }
            else {
                current_ones++;
            }
            if (current_ones > max_ones) {
                max_ones = current_ones;
            }
        }
        prev_char = str[i];
    }

    printf("%d ", max_zeros);
    printf("%d", max_ones);

    return 0;
}