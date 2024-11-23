#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 10000

int main() {
    int count = 0;
    char find[] = "어린 왕자";
    char buffer[BUFFER_SIZE];
    int buffer_index = 0;

    FILE *file = fopen("TheLittlePrince.txt", "r");

    clock_t start = clock();

    printf("'어린 왕자'가 위치한 인덱스:\n");
    // String Matching
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
      // buffer는 **문자 배열(char array)**이고, 문자열의 각 문자를 가리키려면 char * 포인터가 필요합니다. 이것은 각 문자의 주소를 다루기 위해서입니다.
        char *ptr = buffer; 
        char *ptr_find;
      // strstr() 함수는 부분 문자열의 위치를 반환하는데, 그 반환값은 **문자열의 특정 위치를 가리키는 포인터(char *)**입니다.
        while ((ptr_find = strstr(ptr, find)) != NULL) {
            int position = buffer_index + (ptr_find - buffer);
            // **ptr_find - buffer**는 **현재 버퍼 내에서 ptr_find가 buffer의 시작으로부터 얼마나 떨어져 있는지(인덱스)**를 계산합니다.
            // 예를 들어, 만약 "어린 왕자"가 버퍼의 3번째 위치에서 시작한다면, ptr_find - buffer는 2 (0부터 시작하는 인덱스)와 같은 값을 갖습니다.
            printf("%d, ", position);
            count++;
            ptr = ptr_find + strlen(find);
            // strstr() 함수는 주어진 위치에서 처음으로 일치하는 문자열만 찾습니다. 따라서 한 번 "어린 왕자"를 찾고 나면, 그 다음 위치부터 다시 검색을 시작해야 합니다. 
            // **ptr = ptr_find + strlen(find);**는 "어린 왕자" 문자열이 끝난 이후의 위치를 가리키도록 ptr을 업데이트합니다.
        }
        buffer_index += strlen(buffer);
    }

    printf("\n총 %d번 언급됨.",count);

    clock_t end = clock();

    printf("\n\n소요 시간: %lf초\n", (double)(end - start) / CLOCKS_PER_SEC);
    fclose(file);

    return 0;
}
