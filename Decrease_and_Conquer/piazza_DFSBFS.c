#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 11

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node* adjList[MAX_VERTICES];
    int visited[MAX_VERTICES];
} Graph;

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    if (!graph->adjList[src] || graph->adjList[src]->vertex > dest) {
        newNode->next = graph->adjList[src];
        graph->adjList[src] = newNode;
    } else {
        Node* temp = graph->adjList[src];
        while (temp->next && temp->next->vertex < dest) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // dest -> src (양방향 그래프이므로 반대 방향 추가)
    newNode = createNode(src);
    if (!graph->adjList[dest] || graph->adjList[dest]->vertex > src) {
        newNode->next = graph->adjList[dest];
        graph->adjList[dest] = newNode;
    } else {
        Node* temp = graph->adjList[dest];
        while (temp->next && temp->next->vertex < src) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}


int found = 0; 
void DFS(Graph* graph, int vertex, int target) {
    if (found) return;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    if (vertex == target) {
        found = 1; 
        return;
    }

    Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex, target);
        }
        if (found) return;
        temp = temp->next;
    }
}

void BFS(Graph* graph, int startVertex, int target) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    graph->visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front != rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        if (currentVertex == target) {
            return; 
        }

        Node* temp = graph->adjList[currentVertex];
        while (temp != NULL) {
            int connectedVertex = temp->vertex;

            if (!graph->visited[connectedVertex]) {
                graph->visited[connectedVertex] = 1;
                queue[rear++] = connectedVertex;
            }
            temp = temp->next;
        }
    }
}

void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

int main() {
    Graph* graph = createGraph(11);

    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 5);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 5, 6);
    addEdge(graph, 6, 7);
    addEdge(graph, 6, 9);
    addEdge(graph, 7, 8);
    addEdge(graph, 9, 8);
    addEdge(graph, 9, 10);

    int startVertex = 5;
    int targetVertex = 9;

    printf("DFS 탐색 경로: ");
    found = 0;
    DFS(graph, startVertex, targetVertex);
    printf("\n");

    resetVisited(graph);

    printf("BFS 탐색 경로: ");
    BFS(graph, startVertex, targetVertex);
    printf("\n");

    return 0;
}
