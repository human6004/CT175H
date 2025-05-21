#include <stdio.h>

int main() {
    int m, n;
    int a[100][100]; // Kích thước tối đa 100x100
    int count = 0;

    // Nhập số hàng và số cột
    scanf("%d %d", &m, &n);

    // Nhập ma trận và đếm phần tử > 0
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] > 0) count++;
        }
    }

    // In kết quả
    printf("%d\n", count);
    return 0;
}
