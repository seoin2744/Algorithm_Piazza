#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define INF INT_MAX

typedef struct {
    int u, v, weight;
} Edge;

const char *vertex_names[] = {"s", "t", "x", "y", "z"};

void print_path(int predecessor[], int target) {
    if (target == -1) {
        return;
    }
    print_path(predecessor, predecessor[target]);
    printf("%s ", vertex_names[target]);
}

void bellmanFord(Edge edges[], int vertices, int edgesCount, int source) {
    int distance[vertices];
    int predecessor[vertices];

    for (int i = 0; i < vertices; i++) {
        distance[i] = INF;
        predecessor[i] = -1;
    }
    distance[source] = 0;

    for (int i = 0; i < vertices - 1; i++) {
        for (int j = 0; j < edgesCount; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].weight;

            if (distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                predecessor[v] = u;
            }
        }
    }

    for (int j = 0; j < edgesCount; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int weight = edges[j].weight;

        if (distance[u] != INF && distance[u] + weight < distance[v]) {
            printf("Graph contains a negative weight cycle\n");
            return;
        }
    }

    printf("Vertex\tDistance\tPath\n");
    for (int i = 0; i < vertices; i++) {
        printf("%s\t", vertex_names[i]);
        if (distance[i] == INF) {
            printf("INF\t\tNo Path\n");
        } else {
            printf("%d\t\t", distance[i]);
            print_path(predecessor, i);
            printf("\n");
        }
    }
}

int main() {
    int vertices = 5; 
    int edgesCount = 10;

    // 간선 배열 정의 (s=0, t=1, x=2, y=3, z=4)
    Edge edges[] = {
        {0, 1, 6},   // s -> t
        {0, 3, 7},   // s -> y
        {1, 2, 5},   // t -> x
        {1, 3, 8},   // t -> y
        {1, 4, -4},  // t -> z
        {2, 1, -2},  // x -> t
        {3, 2, -3},  // y -> x
        {3, 4, 9},   // y -> z
        {4, 0, 2},   // z -> s
        {4, 2, 7}    // z -> x
    };

    int source = 0; // 시작점: s (0번 정점)
    bellmanFord(edges, vertices, edgesCount, source);

    return 0;
}
