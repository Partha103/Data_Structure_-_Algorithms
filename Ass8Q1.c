#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int weight;
    struct Node* next;
};

struct Graph {
    int V;
    struct Node** adjList;
};

struct Node* createNode(int data, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        struct Node* current = graph->adjList[i];
        printf("Adjacency list of vertex %d: ", i);
        while (current != NULL) {
            printf("(%d, %d) -> ", current->data, current->weight);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int V = 5;

    struct Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 3);
    addEdge(graph, 0, 3, 2);
    addEdge(graph, 0, 8, 4);
    addEdge(graph, 1, 7, 4);
    addEdge(graph, 8, 4, 8);
    addEdge(graph, 4, 3, 1);
    addEdge(graph, 3, 2, 6);
    addEdge(graph, 2, 5, 1);
    addEdge(graph, 2, 7, 2);
    addEdge(graph, 5, 6, 8);

    printGraph(graph);

    return 0;
}
