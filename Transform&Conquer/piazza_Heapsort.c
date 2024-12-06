#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMinHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

void buildMaxHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int data[] = {82, 45, 37, 59, 68, 19, 34, 27, 98, 11, 52, 77, 49, 25, 64, 15, 90, 30, 88, 73, 50, 33, 92, 61, 80, 57, 39, 21, 94, 13, 60, 48, 53, 18, 95, 74, 67, 72, 87, 100};
    int n = sizeof(data) / sizeof(data[0]);

    int minHeap[n];
    for (int i = 0; i < n; i++) minHeap[i] = data[i];
    buildMinHeap(minHeap, n);
    printf("Min-Heap:\n");
    printArray(minHeap, n);

    int maxHeap[n];
    for (int i = 0; i < n; i++) maxHeap[i] = data[i];
    buildMaxHeap(maxHeap, n);
    printf("Max-Heap:\n");
    printArray(maxHeap, n);

    return 0;
}
