#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

void quickSort(int arr[], int left, int right) {
    if (left >= right) return;

    int pivot = arr[left];
    int i = left + 1, j = right, temp;

    while (i <= j) {
        while (i <= right && arr[i] <= pivot) i++;
        while (j > left && arr[j] >= pivot) j--;
        if (i > j) {
            temp = arr[j];
            arr[j] = arr[left];
            arr[left] = temp;
        } else {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    quickSort(arr, left, j - 1);
    quickSort(arr, j + 1, right);
}

int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int main() {
    int arr[SIZE];
    char input[10];
    int target, index;

    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100000; 
    }
    quickSort(arr, 0, SIZE - 1);

    printf("정렬된 배열의 값들:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    while (1) {
        printf("찾을 값을 입력하세요 (종료: Q): ");
        scanf("%s", input);

        if (input[0] == 'Q' || input[0] == 'q') {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        target = atoi(input);
        index = binarySearch(arr, SIZE, target);

        if (index != -1) {
            printf("값 %d은(는) 배열의 %d번째 인덱스에 있습니다.\n", target, index);
        } else {
            printf("값 %d은(는) 배열에 존재하지 않습니다.\n", target);
        }
    }

    return 0;
}
