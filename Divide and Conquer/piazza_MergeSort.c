#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100

int sorted[MAX_SIZE];

void print_array(int list[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

void merge(int list[], int left, int mid, int right) {
    int i, j, k, l;
    i = left;  
    j = mid + 1; 
    k = left;       // 결과 배열

    while (i <= mid && j <= right) {
        if (list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }

    if (i > mid) {
        for (l = j; l <= right; l++)
            sorted[k++] = list[l];
    } else {
        for (l = i; l <= mid; l++)
            sorted[k++] = list[l];
    }

    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
    }
}

void merge_sort(int list[], int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;

        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

int main() {
    int list[MAX_SIZE] = {0};
    srand(time(0));

    for (int k = 0; k < MAX_SIZE; k++) {
        list[k] = rand() ;
    }

    printf("Original array:\n");
    print_array(list, MAX_SIZE);

    clock_t start = clock();
    merge_sort(list, 0, MAX_SIZE - 1);
    clock_t end = clock();

    printf("\nSorted array:\n");
    print_array(list, MAX_SIZE);

    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n running time: %f seconds\n", duration);

    return 0;
}
