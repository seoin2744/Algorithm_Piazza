#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define N 5
#define INF INT_MAX

// 노드 구조체
typedef struct {
    int level;
    int path[N];
    int bound;
} Node;

typedef struct {
    Node nodes[1000];
    int size;
} PriorityQueue;

int matrix[N][N] = {
    {0, 14, 4, 10, 20},
    {14, 0, 7, 8, 7},
    {4, 5, 0, 7, 16},
    {11, 7, 9, 0, 2},
    {18, 7, 17, 4, 0}
};

// 우선순위 큐 관련 함수들
void initialize(PriorityQueue *pq) {
    pq->size = 0;
}

void insert(PriorityQueue *pq, Node node) {
    pq->nodes[pq->size++] = node;
}

bool isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

Node removeMin(PriorityQueue *pq) {
    int minIndex = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->nodes[i].bound < pq->nodes[minIndex].bound)
            minIndex = i;
    }
    Node minNode = pq->nodes[minIndex];
    pq->nodes[minIndex] = pq->nodes[--pq->size];
    return minNode;
}

// 경계(bound)를 계산하는 함수
int bound(Node node) {
    int lower_bound = 0;
    bool visited[N] = {false};

    // 이미 방문한 노드 처리
    for (int i = 0; i <= node.level; i++)
        visited[node.path[i]] = true;

    // 부분 경로 비용
    for (int i = 0; i < node.level; i++)
        lower_bound += matrix[node.path[i]][node.path[i + 1]];

    // 남은 행에 대한 최소 비용 추가
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            int min = INF;
            for (int j = 0; j < N; j++) {
                if (i != j && !visited[j])
                    if (matrix[i][j] < min)
                        min = matrix[i][j];
            }
            lower_bound += min;
        }
    }
    return lower_bound;
}

// Branch & Bound 알고리즘
void travel2(int n, int matrix[N][N], int *opttour, int *minlength) {
    PriorityQueue pq;
    initialize(&pq);

    Node v, u;
    v.level = 0;
    v.path[0] = 0; // 시작점: 노드 0
    v.bound = bound(v);
    *minlength = INF;

    insert(&pq, v);

    while (!isEmpty(&pq)) {
        v = removeMin(&pq);

        if (v.bound < *minlength) {
            for (int i = 1; i < n; i++) {
                bool alreadyVisited = false;
                for (int j = 0; j <= v.level; j++) {
                    if (v.path[j] == i) {
                        alreadyVisited = true;
                        break;
                    }
                }
                if (!alreadyVisited) {
                    u.level = v.level + 1;
                    for (int k = 0; k <= v.level; k++)
                        u.path[k] = v.path[k];
                    u.path[u.level] = i;

                    if (u.level == n - 2) {
                        for (int k = 1; k < n; k++) {
                            bool visited = false;
                            for (int l = 0; l <= u.level; l++)
                                if (u.path[l] == k)
                                    visited = true;
                            if (!visited) {
                                u.path[u.level + 1] = k;
                                break;
                            }
                        }
                        u.path[u.level + 2] = 0;
                        int length = 0;
                        for (int k = 0; k <= n; k++)
                            length += matrix[u.path[k]][u.path[k + 1]];
                        if (length < *minlength) {
                            *minlength = length;
                            for (int k = 0; k <= n; k++)
                                opttour[k] = u.path[k];
                        }
                    } else {
                        u.bound = bound(u);
                        if (u.bound < *minlength)
                            insert(&pq, u);
                    }
                }
            }
        }
    }
}

int main() {
    int opttour[N + 1];
    int minlength;
    travel2(N, matrix, opttour, &minlength);

    printf("최적 경로: ");
    for (int i = 0; i <= N; i++)
        printf("%d ", opttour[i]);
    printf("\n최소 비용: %d\n", minlength);

    return 0;
}
