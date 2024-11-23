#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 1000

int sorted[MAX_SIZE];

void print_array(int list[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int temp= *a;
    *a=*b;
    *b=temp;
}

int partition(int list[], int left, int right) {
    int pivot = list[left];
    int i = left+1;
    int j = right;

    while (1) {
        while (i <= right && list[i] <= pivot) i++;
        while (j > left && list[j] > pivot) j--;

        if (i >= j) break; 
        swap(&list[i], &list[j]);
    }
    swap(&list[left], &list[j]); 
    return j; 
}

void quick_sort(int list[], int left, int right) {
    if (left<right) {
        int p = partition(list, left, right);

        quick_sort(list,left,p-1);
        quick_sort(list,p+1,right);
    }
}

int main() {
    int list[MAX_SIZE] = {0};

    srand(time(0));

    for (int k = 0; k < MAX_SIZE; k++) {
        list[k] = rand() % 10000;
    }

    printf("Original array:\n");
    print_array(list, MAX_SIZE);

    clock_t start = clock();
    quick_sort(list, 0, MAX_SIZE - 1);
    clock_t end = clock();

    printf("\nSorted array:\n");
    print_array(list, MAX_SIZE);

    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n running time: %f seconds\n", duration);

    return 0;
}
