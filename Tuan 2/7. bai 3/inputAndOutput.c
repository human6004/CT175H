#include <stdio.h>

// Hàm hoán đổi hai số
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Hàm sắp xếp mảng tăng dần (sử dụng Bubble Sort)
void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}
int main(int argc, char** argv) {
    int a;
    scanf("%d  ",&a);
    int arr[a];
    for(int i=0; i<a; i++){
        scanf("%d", &arr[i]);
    }
    sortArray(arr,a);
    for(int i=0; i<a; i++){
        printf("%d ", arr[i]);
    }
	return 0;
}