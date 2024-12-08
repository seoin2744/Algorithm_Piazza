#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100
#define MAX_EDGES 100

typedef struct {
    char u, v;  
    int weight; 
} Edge;

int find(int parent[], int node) {
    if (parent[node] == node) return node;
    return parent[node] = find(parent, parent[node]); 
}

void union_sets(int parent[], int rank[], int u, int v) {
    int rootU = find(parent, u);
    int rootV = find(parent, v);

    if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

int compare_edges(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->weight - edgeB->weight;
}

void kruskal(Edge edges[], int numEdges, int numNodes) {
    int parent[MAX_NODES], rank[MAX_NODES];
    Edge mst[MAX_EDGES];  
    int mstIndex = 0, totalWeight = 0;

    for (int i = 0; i < numNodes; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    qsort(edges, numEdges, sizeof(Edge), compare_edges);

    printf("=== Kruskal's Algorithm 과정 ===\n");
    for (int i = 0; i < numEdges; i++) {
        int u = edges[i].u - 'A'; 
        int v = edges[i].v - 'A'; 

        if (find(parent, u) != find(parent, v)) {
            union_sets(parent, rank, u, v);
            mst[mstIndex++] = edges[i];
            totalWeight += edges[i].weight;
            printf("%c → %c (가중치: %d)\n", edges[i].u, edges[i].v, edges[i].weight);
        }
    }

    printf("\n=== Minimum Spanning Tree (MST) ===\n");
    for (int i = 0; i < mstIndex; i++) {
        printf("%c → %c (가중치: %d)\n", mst[i].u, mst[i].v, mst[i].weight);
    }
    printf("\n총 가중치: %d\n", totalWeight);
}

int main() {
    Edge edges[MAX_EDGES] = {
        {'A', 'B', 2}, {'A', 'C', 4},
        {'B', 'C', 3}, {'B', 'D', 9}, {'B', 'G', 4}, {'B', 'H', 2},
        {'C', 'D', 1}, {'C', 'E', 3},
        {'D', 'E', 3}, {'D', 'F', 3}, {'D', 'G', 1},
        {'E', 'F', 2},
        {'F', 'G', 6},
        {'G', 'H', 14}
    };

    int numEdges = 13;  
    int numNodes = 8; 

    kruskal(edges, numEdges, numNodes);

    return 0;
}
