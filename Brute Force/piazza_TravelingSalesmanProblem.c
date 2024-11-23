#include <stdio.h>  // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <limits.h> // INT_MAX 등의 상수를 사용하기 위한 헤더 파일
#include <time.h>   // 시간 측정을 위한 헤더 파일

#define V 5 // vertax 5개

// 각 도시 간의 이동 비용을 나타내는 2차원 배열
int graph[V][V] = { // graph[i][j] i : 출발정점, j : 도착정점
    {0, 2, 3, 2, 3},
    {2, 0, 3, 4, 1},
    {3, 3, 0, 2, 4},
    {2, 4, 2, 0, 5},
    {3, 1, 4, 5, 0}
};


// 두 정수의 포인터를 받아 그 값을 교환하는 함수
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 주어진 배열의 다음 순열을 생성하는 함수
int next_permutation(int *array, int size) {
    int i = size - 1;
    // 주어진 순열에서 다음으로 큰 순열을 찾기 위한 과정
    // i = size - 1은 배열의 마지막 인덱스부터 탐색을 시작합니다.
    while (i > 0 && array[i - 1] >= array[i]) i--;
    // array[i - 1] >= array[i] 조건은 내림차순인지를 검사하는 부분입니다. 배열이 내림차순으로 정렬되어 있으면, 더 큰 순열이 없습니다.
    // 내림차순이 끝나는 지점을 찾기 위해 인덱스를 줄입니다. i가 0이 될 때까지 계속 줄여나가며 내림차순이 유지되는 한 계속 탐색합니다.
    
    if (i <= 0) return 0;  // 더 이상 순열이 없으면 0을 반환

    int j = size - 1;
    // i - 1 위치의 값보다 큰 값 중 가장 작은 값을 가진 인덱스 j
    while (array[j] <= array[i - 1]) j--;
    // i - 1 위치의 값보다 큰 값 중 가장 작은 값을 가진 인덱스 j를 찾습니다.
    // 배열의 끝에서부터 array[j]가 array[i - 1]보다 클 때까지 찾습니다. 이는 사전순으로 다음 순열을 만들기 위해 필요한 단계입니다.
    // 예시 ) array = [1, 3, 5, 4, 2]에서, i = 2이고 array[i - 1] = 3입니다. 이제 array[j]는 array[i - 1] = 3보다 큰 값 중에서 가장 작은 값인 4가 됩니다. 따라서 j = 3이 됩니다


    // i - 1의 값은 내림차순이 깨지는 위치입니다. 
    // 즉, 배열의 앞부분은 작은 순서대로 정렬되어 있지만, i - 1부터는 내림차순이 됩니다. 
    // 이 위치에서 값을 더 큰 값으로 교체하여 다음 순열을 만듭니다. 
    // 하지만 더 큰 값 중에서도 가능한 한 작은 값으로 교체해야 "다음 순열"이 사전순으로 가장 가까운 순열이 됩니다.

    swap(&array[i - 1], &array[j]);  // 두 요소를 교환

    j = size - 1;
    while (i < j) {
        swap(&array[i], &array[j]);  // 순열의 나머지 부분을 뒤집음
        i++;
        j--;
    }

    // i - 1과 j를 교환한 후, i부터 배열의 끝까지는 내림차순으로 정렬되어 있습니다. 이 부분을 뒤집으면 오름차순이 되어 사전순으로 가장 작은 배열이 됩니다.
    // 예를 들어, 교환 후 배열이 [1, 4, 5, 3, 2]라면, 5, 3, 2는 내림차순입니다. 이를 뒤집으면 [2, 3, 5]가 되어 배열은 [1, 4, 2, 3, 5]가 됩니다. 이게 바로 "다음 순열"입니다.


    return 1;  // 순열 생성 성공
}

// 모든 가능한 경로와 그 비용을 찾고, 최단 경로를 출력하는 함수
void findAllPaths() {
    int vertex[V]; //크기가 V인 정수 vertex 배열. 도시(정점)의 인덱스를 저장하는 데 사용됨. 
    for (int i = 0; i < V; i++)
        vertex[i] = i;  // 도시 인덱스 초기화
    // for 루프를 사용하여 배열 vertex의 각 원소를 해당 인덱스 값으로 초기화. => 도시 0부터 도시 4까지 순차적으로 번호를 부여.

    int minPathCost = INT_MAX;
    // INT_MAX와 INT_MIN은 C 언어에서 최대와 최소 정수 값을 나타내는 매크로로, limits.h 헤더 파일에 미리 정의되어 있습니다. 
    // 이 매크로들은 사용자가 따로 define으로 지정할 필요 없이, limits.h 헤더 파일을 포함하기만 하면 바로 사용할 수 있습니다.

    int bestPath[V]; // **최소 비용 경로의 순서(도시 방문 순서)**를 저장해 두기 위해 배열이 필요

    do {
        int currentCost = 0;
        printf("경로: ");
        for (int i = 0; i < V; i++) {
            printf("%d ", vertex[i] + 1);  // 현재 경로 출력, next_permutation 함수가 배열 vertex의 값을 변경함.
            if (i < V - 1) currentCost += graph[vertex[i]][vertex[i + 1]];  // 경로 비용 계산
            // i < V - 1 : 마지막 도시에서 그 다음 도시로 이동하지 않기 위해
            // i가 V - 1이 되면 vertex[V]를 참조하게 되는데, 배열의 인덱스 범위를 초과하게 됩니다. 즉, 배열의 마지막 인덱스는 V - 1까지이므로, vertex[V]는 존재하지 않습니다
        }
        currentCost += graph[vertex[V - 1]][vertex[0]];  // 시작점으로 돌아오는 비용 추가
        printf("-> %d (비용: %d)\n", vertex[0] + 1, currentCost);

        if (currentCost < minPathCost) {
            minPathCost = currentCost;  // 최소 비용 갱신
            for (int i = 0; i < V; i++) {
                bestPath[i] = vertex[i];  // 최단 경로 저장
            }
        }
    } while (next_permutation(vertex + 1, V - 1));  // 다음 순열 생성
    // do 블록 안의 코드를 무조건 한 번 실행합니다.
    // while의 조건식을 검사합니다.
    // **참(true)**일 경우, 다시 do 블록의 내용을 반복 실행합니다.
    // **거짓(false)**일 경우, 반복을 종료하고 그 다음 코드로 넘어갑니다.


    printf("\n최단 경로: ");
    for (int i = 0; i < V; i++) {
        printf("%d ", bestPath[i] + 1);  // 최단 경로 출력
    }
    printf("-> %d (최소 비용: %d)\n", bestPath[0] + 1, minPathCost);
}

// 메인 함수
int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();  // 프로그램 실행 시작 시간 측정
    printf("모든 경로와 그 비용:\n");
    findAllPaths();
    end = clock();  // 프로그램 실행 종료 시간 측정

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  // 총 실행 시간 계산
    printf("실행 시간: %f 초\n", cpu_time_used);
    return 0;
}
