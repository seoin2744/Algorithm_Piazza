#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 30000

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int arr[], int left, int right) {
    if (left >= right) return;

    int pivot = arr[left];
    int i = left + 1, j = right;

    while (i <= j) {
        while (i <= right && arr[i] <= pivot) i++;
        while (j > left && arr[j] >= pivot) j--;
        if (i < j) swap(&arr[i], &arr[j]);
    }
    swap(&arr[left], &arr[j]);

    quickSort(arr, left, j - 1);
    quickSort(arr, j + 1, right);
}

int BruteForce(int arr[], int size, int result[]) {
    int uniqueCount = 0;

    for (int i = 0; i < size; i++) {
        int isDuplicate = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (arr[i] == result[j]) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            result[uniqueCount++] = arr[i];
        }
    }
    return uniqueCount;
}

int Presorting(int arr[], int size, int result[]) {
    quickSort(arr, 0, size - 1); 

    int uniqueCount = 0;
    result[uniqueCount++] = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[i - 1]) {
            result[uniqueCount++] = arr[i];
        }
    }
    return uniqueCount;
}

void generateData(int arr[], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000; 
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}

int main() {
    int arr[SIZE], bruteResult[SIZE], sortResult[SIZE];
    int sizeBrute, sizeSort;
    clock_t start, end;

    generateData(arr, SIZE);

    start = clock();
    sizeBrute = BruteForce(arr, SIZE, bruteResult);
    end = clock();
    double bruteTime = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    sizeSort = Presorting(arr, SIZE, sortResult);
    end = clock();
    double sortTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Brute Force 방식 실행 시간: %.5f초\n", bruteTime);
    printf("Presorting 방식 실행 시간: %.5f초\n", sortTime);

    return 0;
}
