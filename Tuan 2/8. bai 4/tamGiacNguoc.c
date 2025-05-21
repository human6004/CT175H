#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n); 

    for (int i = 1; i <= n; i++) {
        // In khoảng trắng
        for (int j = 1; j <= n - i; j++) {
            printf(" ");
        }

        // In dấu *
        for (int j = 1; j <= 2 * i - 1; j++) {
            printf("*");
        }

        printf("\n");
    }

    return 0;
}
