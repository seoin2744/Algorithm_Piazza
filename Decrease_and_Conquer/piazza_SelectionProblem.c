#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 10000

int SelectionProb(int arr[], int left, int right, int find_idx);
int Pivot(int arr[], int left, int right);
void swap(int arr[], int x, int y);
void PrintArr(int arr[], int size);

int main(void) {
    int arr[MAX_SIZE];
    int k, result;

    srand(time(0)); 
    for (int i = 0; i < MAX_SIZE; i++) {
        arr[i] = rand() % 100000;
    }

    printf("0에서 %d 사이의 k값을 입력하세요: ", MAX_SIZE - 1);
    scanf("%d", &k);

    if (k < 0 || k >= MAX_SIZE) {
        printf("k값이 유효하지 않습니다. 프로그램을 종료합니다.\n");
        return 0;
    }

    result = SelectionProb(arr, 0, MAX_SIZE - 1, k);

    printf("k(%d)번째 값: %d\n", k, result);

    return 0;
}

int SelectionProb(int arr[], int left, int right, int find_idx) {
    int p_idx = Pivot(arr, left, right);

    if (p_idx == find_idx) {
        return arr[p_idx];
    } else if (p_idx > find_idx) {
        return SelectionProb(arr, left, p_idx - 1, find_idx);
    } else {
        return SelectionProb(arr, p_idx + 1, right, find_idx);
    }
}

int Pivot(int arr[], int left, int right) {
    int low = left + 1;
    int high = right;
    int pivot = arr[left];

    while (low <= high) {
        while (low <= right && arr[low] <= pivot) low++;
        while (high >= left && arr[high] > pivot) high--;
        if (low < high) {
            swap(arr, low, high);
        }
    }

    swap(arr, left, high);

    return high;
}

void swap(int arr[], int x, int y) {
    int tmp = arr[x];
    arr[x] = arr[y];
    arr[y] = tmp;
}

void PrintArr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}
