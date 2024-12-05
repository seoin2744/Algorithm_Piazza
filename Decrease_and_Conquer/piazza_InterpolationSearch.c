#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000

int interpolation(int arr[], int size, int key) {
    int low = 0, high = size - 1;

    while (low <= high && key >= arr[low] && key <= arr[high]) {
        int pos = low + ((key - arr[low]) * (high - low)) / (arr[high] - arr[low]);

        if (arr[pos] == key) {
            return pos;
        }

        if (arr[pos] < key) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    return -1; 
}

void generateData(int arr[], int size) {
    arr[0] = rand() % 10;
    for (int i = 1; i < size; i++) {
        arr[i] = arr[i - 1] + rand() % 10 + 1; 
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

int main() {
    int arr[SIZE];
    int key, result;

    srand(time(0)); 

    generateData(arr, SIZE);

    printf("정렬된 데이터:\n");
    printArray(arr, SIZE);

    printf("찾을 값을 입력하세요: ");
    scanf("%d", &key);

    result = interpolation(arr, SIZE, key);

    if (result != -1) {
        printf("값 %d은(는) 배열의 %d번째 인덱스에 있습니다.\n", key, result);
    } else {
        printf("값 %d은(는) 배열에 존재하지 않습니다.\n", key);
    }

    return 0;
}
