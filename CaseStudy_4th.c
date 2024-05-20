// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <limits.h>

// #define MAX_AIRPORTS 41000

// struct Airport {
//     int id;
//     double x, y;
//     int capacity;
//     int visited;
// };

// struct Edge {
//     int dest;
//     double weight;
//     struct Edge* next;
// };

// struct Graph {
//     int V;
//     struct Edge** adjList;
// };

// struct RTreeNode {
//     double x_min, x_max, y_min, y_max;
//     struct Airport* airport;
//     struct RTreeNode* left;
//     struct RTreeNode* right;
// };

// struct MinHeapNode {
//     int v;
//     double key;
// };

// struct MinHeap {
//     int size;
//     int capacity;
//     int* pos;
//     struct MinHeapNode** array;
// };

// struct MSTNode {
//     int parent;
//     double weight;
// };

// void insertAirport(struct RTreeNode** root, struct Airport* airport) {
//     if (*root == NULL) {
//         *root = (struct RTreeNode*)malloc(sizeof(struct RTreeNode));
//         (*root)->x_min = (*root)->x_max = airport->x;
//         (*root)->y_min = (*root)->y_max = airport->y;
//         (*root)->airport = airport;
//         (*root)->left = (*root)->right = NULL;
//         return;
//     }

//     if (airport->x < (*root)->x_min) {
//         (*root)->x_min = airport->x;
//     } else if (airport->x > (*root)->x_max) {
//         (*root)->x_max = airport->x;
//     }

//     if (airport->y < (*root)->y_min) {
//         (*root)->y_min = airport->y;
//     } else if (airport->y > (*root)->y_max) {
//         (*root)->y_max = airport->y;
//     }

//     if (airport->x < (*root)->airport->x || (airport->x == (*root)->airport->x && airport->y < (*root)->airport->y)) {
//         insertAirport(&((*root)->left), airport);
//     } else {
//         insertAirport(&((*root)->right), airport);
//     }
// }

// struct RTreeNode* createRTree(struct Airport* airports[], int n) {
//     struct RTreeNode* root = NULL;
//     for (int i = 0; i < n; i++) {
//         insertAirport(&root, airports[i]);
//     }
//     return root;
// }

// double calcDistance(struct Airport* a, struct Airport* b) {
//     return sqrt(pow((a->x - b->x), 2) + pow((a->y - b->y), 2));
// }

// struct Graph* createGraph(int V) {
//     struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
//     graph->V = V;
//     graph->adjList = (struct Edge**)malloc(V * sizeof(struct Edge*));
//     for (int i = 0; i < V; i++) {
//         graph->adjList[i] = NULL;
//     }
//     return graph;
// }

// void addEdge(struct Graph* graph, int src, int dest, double weight) {

//     struct Edge* newNode = (struct Edge*)malloc(sizeof(struct Edge));
//     newNode->dest = dest;
//     newNode->weight = weight;
//     newNode->next = graph->adjList[src];
//     graph->adjList[src] = newNode;


//     newNode = (struct Edge*)malloc(sizeof(struct Edge));
//     newNode->dest = src;
//     newNode->weight = weight;
//     newNode->next = graph->adjList[dest];
//     graph->adjList[dest] = newNode;
// }

// struct MinHeapNode* newMinHeapNode(int v, double key) {
//     struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
//     minHeapNode->v = v;
//     minHeapNode->key = key;
//     return minHeapNode;
// }

// struct MinHeap* createMinHeap(int capacity) {
//     struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
//     minHeap->pos = (int*)malloc(capacity * sizeof(int));
//     minHeap->size = 0;
//     minHeap->capacity = capacity;
//     minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
//     return minHeap;
// }

// void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
//     struct MinHeapNode* t = *a;
//     *a = *b;
//     *b = t;
// }

// void minHeapify(struct MinHeap* minHeap, int idx) {
//     int smallest, left, right;
//     smallest = idx;
//     left = 2 * idx + 1;
//     right = 2 * idx + 2;

//     if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key) {
//         smallest = left;
//     }

//     if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key) {
//         smallest = right;
//     }

//     if (smallest != idx) {

//         struct MinHeapNode* smallestNode = minHeap->array[smallest];
//         struct MinHeapNode* idxNode = minHeap->array[idx];


//         minHeap->pos[smallestNode->v] = idx;
//         minHeap->pos[idxNode->v] = smallest;


//         swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

//         minHeapify(minHeap, smallest);
//     }
// }

// int isEmpty(struct MinHeap* minHeap) {
//     return minHeap->size == 0;
// }

// struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
//     if (isEmpty(minHeap)) {
//         return NULL;
//     }

//     struct MinHeapNode* root = minHeap->array[0];


//     struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
//     minHeap->array[0] = lastNode;


//     minHeap->pos[root->v] = minHeap->size - 1;
//     minHeap->pos[lastNode->v] = 0;


//     --minHeap->size;
//     minHeapify(minHeap, 0);

//     return root;
// }

// void decreaseKey(struct MinHeap* minHeap, int v, double key) {

//     int idx = minHeap->pos[v];


//     minHeap->array[idx]->key = key;

//     while (idx && minHeap->array[idx]->key < minHeap->array[(idx - 1) / 2]->key) {
//         // Swap this node with its parent
//         minHeap->pos[minHeap->array[idx]->v] = (idx - 1) / 2;
//         minHeap->pos[minHeap->array[(idx - 1) / 2]->v] = idx;
//         swapMinHeapNode(&minHeap->array[idx], &minHeap->array[(idx - 1) / 2]);

//         idx = (idx - 1) / 2;
//     }
// }

// void printArr(int parent[], int n, struct Airport* airports) {
//     FILE* outputFile = fopen("output.txt", "w");
//     if (outputFile == NULL) {
//         printf("Error opening output file.\n");
//         return;
//     }

//     fprintf(outputFile, "Optimized Routing:\n");
//     for (int i = 1; i < n; ++i) {
//         fprintf(outputFile, "Airport %d to Airport %d\n", parent[i], i);
//     }

//     fclose(outputFile);
// }

// void primMST(struct Graph* graph, struct Airport* airports[], int src, struct MSTNode mst[]) {
//     int V = graph->V;
//     int parent[V];
//     double key[V];
//     struct MinHeap* minHeap = createMinHeap(V);

//     for (int v = 0; v < V; ++v) {
//         parent[v] = -1;
//         key[v] = INT_MAX;
//         minHeap->array[v] = newMinHeapNode(v, key[v]);
//         minHeap->pos[v] = v;
//     }

//     key[src] = 0;
//     decreaseKey(minHeap, src, key[src]);

//     minHeap->size = V;

//     while (!isEmpty(minHeap)) {

//         struct MinHeapNode* minHeapNode = extractMin(minHeap);
//         int u = minHeapNode->v;

//         struct Edge* temp = graph->adjList[u];
//         while (temp != NULL) {
//             int v = temp->dest;

//             if (minHeap->pos[v] < minHeap->size && temp->weight < key[v]) {
//                 key[v] = temp->weight;
//                 parent[v] = u;
//                 decreaseKey(minHeap, v, key[v]);
//                 mst[v].parent = u;
//                 mst[v].weight = temp->weight;
//             }
//             temp = temp->next;
//         }
//     }

//     printArr(parent, V, airports[0]);
// }

// void findMST(struct RTreeNode* root, struct Airport* airports[], struct MSTNode mst[]) {
//     if (root == NULL) return;
//     if (root->airport != NULL) {
//         root->airport->visited = 0;
//     }
//     findMST(root->left, airports, mst);
//     findMST(root->right, airports, mst);
// }

// int main() {
//     FILE* inputFile = fopen("text.txt", "r");
//     if (inputFile == NULL) {
//         printf("Error opening input file.\n");
//         return 1;
//     }

//     int numAirports;
//     fscanf(inputFile, "%d", &numAirports);

//     struct Airport* airports[MAX_AIRPORTS];
//     for (int i = 0; i < numAirports; i++) {
//         int id, capacity;
//         double x, y;
//         fscanf(inputFile, "%d %lf %lf %d", &id, &x, &y, &capacity);
//         airports[i] = (struct Airport*)malloc(sizeof(struct Airport));
//         airports[i]->id = id;
//         airports[i]->x = x;
//         airports[i]->y = y;
//         airports[i]->capacity = capacity;
//         airports[i]->visited = 0;
//     }

//     fclose(inputFile);

//     struct Graph* graph = createGraph(numAirports);

//     for (int i = 0; i < numAirports; i++) {
//         for (int j = i + 1; j < numAirports; j++) {
//             double weight = calcDistance(airports[i], airports[j]);
//             addEdge(graph, i, j, weight);
//         }
//     }

//     struct MSTNode mst[numAirports];
//     primMST(graph, airports, 0, mst);

//     struct RTreeNode* root = createRTree(airports, numAirports);
//     findMST(root, airports, mst);

//     for (int i = 0; i < numAirports; i++) {
//         free(airports[i]);
//     }
//     free(graph->adjList);
//     free(graph);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>

#define MAX_AIRPORTS 41000

// Define struct for Airport
struct Airport {
    int id;
    double x, y;
    int capacity;
    int visited;
};

// Define struct for Edge in the graph
struct Edge {
    int dest;
    double weight;
    struct Edge* next;
};

// Define struct for Graph
struct Graph {
    int V;
    struct Edge** adjList;
};

// Define struct for MinHeapNode
struct MinHeapNode {
    int v;
    double key;
};

// Define struct for MinHeap
struct MinHeap {
    int size;
    int capacity;
    int* pos;
    struct MinHeapNode** array;
};

// Function to create a new MinHeapNode
struct MinHeapNode* newMinHeapNode(int v, double key) {
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->key = key;
    return minHeapNode;
}

// Function to create a MinHeap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Function to swap two MinHeapNodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Function to perform min heapify operation
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key) {
        smallest = right;
    }

    if (smallest != idx) {
        struct MinHeapNode* smallestNode = minHeap->array[smallest];
        struct MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Function to check if MinHeap is empty
int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

// Function to extract minimum node from MinHeap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return NULL;
    }

    struct MinHeapNode* root = minHeap->array[0];
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decrease key value of a vertex v
void decreaseKey(struct MinHeap* minHeap, int v, double key) {
    int idx = minHeap->pos[v];

    minHeap->array[idx]->key = key;

    while (idx && minHeap->array[idx]->key < minHeap->array[(idx - 1) / 2]->key) {
        minHeap->pos[minHeap->array[idx]->v] = (idx - 1) / 2;
        minHeap->pos[minHeap->array[(idx - 1) / 2]->v] = idx;
        swapMinHeapNode(&minHeap->array[idx], &minHeap->array[(idx - 1) / 2]);

        idx = (idx - 1) / 2;
    }
}

// Function to print optimized routing to output file
void printRouting(int parent[], int n, struct Airport* airports[]) {
    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return;
    }

    fprintf(outputFile, "Optimized Routing:\n");
    for (int i = 1; i < n; ++i) {
        fprintf(outputFile, "Airport %d to Airport %d\n", parent[i], i);
    }

    fclose(outputFile);
}

// Function to implement Dijkstra's algorithm for finding shortest paths
void dijkstra(struct Graph* graph, int src, struct Airport* airports[]) {
    int V = graph->V;
    int parent[V];
    double dist[V];
    struct MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {
        parent[v] = -1;
        dist[v] = INFINITY;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        struct Edge* temp = graph->adjList[u];
        while (temp != NULL) {
            int v = temp->dest;

            if (minHeap->pos[v] < minHeap->size && dist[u] != DBL_MAX && (dist[u] + temp->weight) < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    // Print optimized routing
    printRouting(parent, V, airports);
}

// Main function
int main() {
    // Read input data from file
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    int numAirports;
    fscanf(inputFile, "%d", &numAirports);

    struct Airport* airports[MAX_AIRPORTS];
    for (int i = 0; i < numAirports; i++) {
        int id, capacity;
        double x, y;
        fscanf(inputFile, "%d %lf %lf %d", &id, &x, &y, &capacity);
        airports[i] = (struct Airport*)malloc(sizeof(struct Airport));
        airports[i]->id = id;
        airports[i]->x = x;
        airports[i]->y = y;
        airports[i]->capacity = capacity;
        airports[i]->visited = 0;
    }

    fclose(inputFile);

    // Create graph and add edges
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = numAirports;
    graph->adjList = (struct Edge**)malloc(numAirports * sizeof(struct Edge*));
    for (int i = 0; i < numAirports; i++) {
        graph->adjList[i] = NULL;
    }

    // Populate graph with edges (flights)
    for (int i = 0; i < numAirports; i++) {
        for (int j = i + 1; j < numAirports; j++) {
            double weight = sqrt(pow((airports[i]->x - airports[j]->x), 2) + pow((airports[i]->y - airports[j]->y), 2));
            // Assuming weight represents distance between airports
            struct Edge* newNode = (struct Edge*)malloc(sizeof(struct Edge));
            newNode->dest = j;
            newNode->weight = weight;
            newNode->next = graph->adjList[i];
            graph->adjList[i] = newNode;

            newNode = (struct Edge*)malloc(sizeof(struct Edge));
            newNode->dest = i;
            newNode->weight = weight;
            newNode->next = graph->adjList[j];
            graph->adjList[j] = newNode;
        }
    }

    // Perform Dijkstra's algorithm for finding shortest paths
    dijkstra(graph, 0, airports);

    // Cleanup memory
    for (int i = 0; i < numAirports; i++) {
        free(airports[i]);
    }
    for (int i = 0; i < numAirports; i++) {
        struct Edge* current = graph->adjList[i];
        while (current != NULL) {
            struct Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjList);
    free(graph);
    return 0;
}