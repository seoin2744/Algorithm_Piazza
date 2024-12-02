#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 26

typedef struct Node {
    char vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adjList[MAX_VERTICES]; 
    int inDegree[MAX_VERTICES]; 
} Graph;

typedef struct Queue {
    char data[MAX_VERTICES];
    int front;
    int rear;
} Queue;

Node* createNode(char vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjList[i] = NULL;
        graph->inDegree[i] = 0;
    }
    return graph;
}

void addEdge(Graph* graph, char src, char dest) {
    int srcIndex = src - 'a';
    int destIndex = dest - 'a';

    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[srcIndex];
    graph->adjList[srcIndex] = newNode;

    graph->inDegree[destIndex]++;
}

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

void enqueue(Queue* q, char vertex) {
    q->data[q->rear++] = vertex;
}

char dequeue(Queue* q) {
    return q->data[q->front++];
}

int isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

void topologicalSort(Graph* graph) {
    Queue q;
    initQueue(&q);

    for (int i = 0; i < MAX_VERTICES; i++) {
        if (graph->adjList[i] != NULL && graph->inDegree[i] == 0) {
            enqueue(&q, i + 'a');
        }
    }

    printf("Topological Sort: ");
    while (!isQueueEmpty(&q)) {
        char u = dequeue(&q);
        printf("%c ", u);

        Node* temp = graph->adjList[u - 'a'];
        while (temp != NULL) {
            int neighborIndex = temp->vertex - 'a';

            graph->inDegree[neighborIndex]--;
            if (graph->inDegree[neighborIndex] == 0) {
                enqueue(&q, temp->vertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main() {
    Graph* graph = createGraph();

    addEdge(graph, 'm', 'q');
    addEdge(graph, 'm', 'r');
    addEdge(graph, 'm', 'x');
    addEdge(graph, 'n', 'o');
    addEdge(graph, 'n', 'q');
    addEdge(graph, 'o', 'r');
    addEdge(graph, 'o', 's');
    addEdge(graph, 'o', 'v');
    addEdge(graph, 'p', 'o');
    addEdge(graph, 'p', 's');
    addEdge(graph, 'p', 'z');
    addEdge(graph, 'q', 't');
    addEdge(graph, 'r', 'u');
    addEdge(graph, 'r', 'y');
    addEdge(graph, 's', 'r');
    addEdge(graph, 'u', 't');
    addEdge(graph, 'v', 'x');
    addEdge(graph, 'v', 'w');
    addEdge(graph, 'w', 'z');
    addEdge(graph, 'y', 'v');

    topologicalSort(graph);

    return 0;
}
