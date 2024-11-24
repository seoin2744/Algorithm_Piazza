#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int data[], int size) {
    int j;
    int five = -1;

    // Find the last occurrence of the value 5
    for (int i = 0; i < size; i++) {
        if (data[i] == 5) {
            five = i;
        }
    }

    for (int i = 1; i < five; i++) {
        int key = data[i];
        j = i - 1;

        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }

    printf("bold 표시된 5를 삽입정렬하기 직전의 정렬 상태:\n");
    for (int k = 0; k < size; k++) {
        printf("%d ", data[k]);
    }
    printf("\n");

    int key = data[five];
    j = five - 1;
    while (j >= 0 && data[j] > key) {
        data[j + 1] = data[j];
        j--;
    }
    data[j + 1] = key;

    for (int i = 0; i < size; i++) {
        if (data[i] == 5) {
            printf("정렬된 이후의 5 인덱스 번호: %d\n", i);
            break;
        }
    }
}

int main() {
    int data[] = {83, 17, 19, 34, 29, 52, 45, 97, 15, 22, 6, 16, 31, 31, 88, 12, 16, 15, 48, 74,
                  26, 67, 73, 18, 1, 29, 98, 8, 97, 47, 78, 51, 81, 53, 98, 25, 95, 27, 29, 17,
                  8, 66, 40, 27, 58, 14, 37, 67, 63, 35, 20, 54, 38, 78, 71, 55, 25, 53, 80, 59,
                  6, 35, 98, 14, 48, 39, 18, 33, 16, 55, 30, 94, 84, 99, 88, 59, 26, 22, 53, 99,
                  72, 55, 71, 76, 76, 12, 79, 1, 33, 87, 26, 63, 52, 42, 28, 61, 59, 8, 3, 60, 99,
                  54, 36, 93, 59, 46, 77, 9, 81, 66, 53, 42, 43, 79, 64, 43, 1, 16, 77, 42, 94, 44,
                  46, 1, 8, 97, 93, 70, 94, 9, 94, 62, 26, 10, 34, 53, 11, 83, 68, 27, 43, 45, 72,
                  94, 78, 98, 95, 40, 11, 72, 4, 94, 18, 47, 16, 77, 34, 12, 60, 14, 60, 17, 77,
                  21, 75, 85, 87, 73, 65, 49, 87, 98, 48, 22, 26, 21, 22, 94, 90, 75, 63, 22, 33,
                  74, 12, 82, 62, 26, 14, 12, 29, 25, 65, 95, 27, 69, 59, 76, 74, 77, 17, 100, 92,
                  38, 19, 2, 44, 5, 83, 38, 42, 77, 13, 23, 61, 64, 54, 17, 79, 82, 42, 52, 57, 30,
                  12, 100, 65, 80, 81, 61, 13, 19, 68, 33, 88, 77, 48, 48, 48, 55, 39, 26, 61, 66,
                  96, 89, 15, 20, 16, 71, 82, 62, 98, 6, 14, 92, 4, 43, 12, 3, 80, 15, 35, 16, 50,
                  34, 58, 42, 22, 30, 24, 29, 9, 66, 10, 60, 48, 90, 66, 71, 34, 2, 46, 63, 12, 71,
                  10, 47, 59, 52, 41, 77, 8, 72, 83, 46, 5, 43, 97, 91};
    int size = sizeof(data) / sizeof(data[0]);
    
    insertion_sort(data, size);
    
    return 0;
}
