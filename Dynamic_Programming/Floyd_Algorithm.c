#include <stdio.h>
#define INF 99999 
#define N 10       

void floyd_warshall(int graph[N][N]) {
    int dist[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < N; k++) {      
        for (int i = 0; i < N; i++) { 
            for (int j = 0; j < N; j++) { 
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printf("All-Pairs Shortest Path:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dist[i][j] == INF) {
                printf("∞ ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int graph[N][N] = {
        {0, 3, INF, 1, INF, 7, INF, 15, 3, 9},
        {INF, 0, 8, INF, 3, INF, 4, 55, INF, INF},
        {3, INF, 0, 2, INF, 11, INF, 19, 8, INF},
        {INF, 2, INF, 0, 6, INF, 4, INF, 1, INF},
        {1, 1, 3, INF, 0, 1, 10, 3, INF, 1},
        {INF, INF, 3, INF, 6, 0, 4, INF, 3, INF},
        {3, 1, INF, 9, INF, 5, 0, 10, 2, INF},
        {INF, 2, 7, 12, 3, 7, INF, 0, INF, 5},
        {4, 14, INF, 5, INF, 3, INF, 5, 0, 3},
        {INF, 12, 1, INF, 7, INF, 3, INF, 5, 0}
    };

    printf("Original Graph:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (graph[i][j] == INF) {
                printf("∞ ");
            } else {
                printf("%d ", graph[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n");
    floyd_warshall(graph);

    return 0;
}
