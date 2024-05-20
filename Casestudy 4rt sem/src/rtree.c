#include "../includes/rtree.h"
#include "../includes/common.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>

// Define constants
#define MAX_RECTS_PER_NODE 4

// Define structures
struct RTreeNode {
    int num_rects;
    RTreeRect rects[MAX_RECTS_PER_NODE];
    struct RTreeNode* children[MAX_RECTS_PER_NODE];
};

struct EdgeNode {
    int destination;
    float weight;
    struct EdgeNode* next;
};

// Define struct EdgeList representing a linked list of edges for each vertex
struct EdgeList {
    struct EdgeNode* head;
};

// Function to add an edge to the adjacency list
void add_edge(struct EdgeList* list, int destination, float weight) {
    struct EdgeNode* newNode = (struct EdgeNode*)malloc(sizeof(struct EdgeNode));
    newNode->destination = destination;
    newNode->weight = weight;
    newNode->next = list->head;
    list->head = newNode;
}

// Function to free memory allocated for the linked list of edges
void free_list(struct EdgeNode* head) {
    while (head != NULL) {
        struct EdgeNode* temp = head;
        head = head->next;
        free(temp);
    }
}

struct Graph {
    int V;  // Number of vertices
    struct EdgeList* adjList;  // Adjacency list representation
};

struct Edge {
    int dest;   // Destination vertex
    float weight;  // Weight of the edge
    struct Edge* next;    
};

// Define Queue data structure
typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function to create an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue) {
        queue->front = NULL;
        queue->rear = NULL;
    }
    return queue;
}

// Function to check if the queue is empty
bool isQEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue an element into the queue
void enqueue(Queue* queue, int data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
        if (isQEmpty(queue)) {
            queue->front = newNode;
            queue->rear = newNode;
        } else {
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
    }
}

// Function to dequeue an element from the queue
int dequeue(Queue* queue) {
    if (isQEmpty(queue)) {
        // Handle empty queue case
        return INT_MIN; // or any other suitable value
    } else {
        int data = queue->front->data;
        QueueNode* temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
        if (queue->front == NULL) {
            queue->rear = NULL; // Reset rear if the queue becomes empty
        }
        return data;
    }
}

// Function to free memory allocated for the queue
void freeQueue(Queue* queue) {
    while (!isQEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

typedef struct MinHeapNode {
    int v;
    double dist;
} MinHeapNode;

// Define MinHeap structure
typedef struct MinHeap {
    int size;
    int capacity;
    int *pos; // To store positions of nodes in the heap
    MinHeapNode **array;
} MinHeap;

// Function to create a new MinHeapNode
MinHeapNode *newMinHeapNode(int v, double dist) {
    MinHeapNode *minHeapNode = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// Function to create a MinHeap
MinHeap *createMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
    return minHeap;
}

// Function to swap two MinHeapNodes
void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b) {
    MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

// Function to heapify at a given index
void minHeapify(MinHeap *minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Function to check if the MinHeap is empty
bool isEmpty(MinHeap *minHeap) {
    return minHeap->size == 0;
}

// Function to extract the minimum node from MinHeap
MinHeapNode *extractMin(MinHeap *minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    MinHeapNode *root = minHeap->array[0];

    MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decrease the dist value of a given vertex v
void decreaseKey(MinHeap *minHeap, int v, double dist) {
    int i = minHeap->pos[v];

    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

bool route_exists(Airport src, Airport dest, Route* routes, int num_routes) {
    // Loop through each route and check if it connects the source and destination airports
    for (int i = 0; i < num_routes; i++) {
        // Compare airports by their coordinates or unique identifiers, depending on your data structure
        if ((routes[i].sourceAirport.latitude == src.latitude && routes[i].sourceAirport.longitude == src.longitude &&
             routes[i].destinationAirport.latitude == dest.latitude && routes[i].destinationAirport.longitude == dest.longitude) ||
            (routes[i].sourceAirport.latitude == dest.latitude && routes[i].sourceAirport.longitude == dest.longitude &&
             routes[i].destinationAirport.latitude == src.latitude && routes[i].destinationAirport.longitude == src.longitude)) {
            return true;
        }
    }
    // If no matching route is found, return false
    return false;
}

// Function prototypes
static struct RTreeNode* RTreeNodeCreate();
static void RTreeNodeDestroy(struct RTreeNode* node);
static void RTreeInsertRectRecursive(const RTreeRect* rect, int id, struct RTreeNode* node);
static RTreeList* RTreeSearchRecursive(const RTreeRect* rect, const struct RTreeNode* node);

// Create a new R-tree node
static struct RTreeNode* RTreeNodeCreate() {
    struct RTreeNode* node = malloc(sizeof(struct RTreeNode));
    if (!node) {
        perror("Failed to create R-tree node: Memory allocation error.\n");
        return NULL;
    }
    node->num_rects = 0;
    return node;
}

// Destroy an R-tree node and its children recursively
static void RTreeNodeDestroy(struct RTreeNode* node) {
    if (!node) {
        return;
    }
    for (int i = 0; i < node->num_rects; i++) {
        RTreeNodeDestroy(node->children[i]);
    }
    free(node);
}

// Create a new R-tree
RTree* RTreeCreate() {
    RTree* tree = malloc(sizeof(RTree));
    if (!tree) {
        perror("Failed to create R-tree: Memory allocation error.\n");
        return NULL;
    }
    tree->root = RTreeNodeCreate();
    if (!tree->root) {
        free(tree);
        return NULL;
    }
    return tree;
}

// Destroy an R-tree
void RTreeDestroy(RTree* tree) {
    if (!tree) {
        return;
    }
    RTreeNodeDestroy(tree->root);
    free(tree);
}

void RTreeFreeList(RTreeList* list) {
    while (list != NULL) {
        RTreeList* temp = list;
        list = list->next;
        free(temp);
    }
}

// Insert a rectangle into the R-tree
void RTreeInsertRect(const RTreeRect* rect, int id, RTree* tree) {
    if (!rect || !tree) {
        return;
    }
    RTreeInsertRectRecursive(rect, id, tree->root);
}

// Helper function to calculate the area of a rectangle
static float rect_area(const RTreeRect* rect) {
    return (rect->max[0] - rect->min[0]) * (rect->max[1] - rect->min[1]);
}

// Helper function to calculate the enlargement of a rectangle after including another rectangle
static float rect_enlargement(const RTreeRect* rect, const RTreeRect* new_rect) {
    float area_before = rect_area(rect);
    RTreeRect enlarged_rect = {
        .min = {
            fmin(rect->min[0], new_rect->min[0]),
            fmin(rect->min[1], new_rect->min[1])},
        .max = {
            fmax(rect->max[0], new_rect->max[0]),
            fmax(rect->max[1], new_rect->max[1])}};
    float area_after = rect_area(&enlarged_rect);
    return area_after - area_before;
}

// Helper function to choose the best child node for insertion
static struct RTreeNode* choose_best_child(const RTreeRect* rect, struct RTreeNode* node) {
    float min_enlargement = FLT_MAX;
    struct RTreeNode* best_child = NULL;

    for (int i = 0; i < node->num_rects; i++) {
        float enlargement = rect_enlargement(&(node->rects[i]), rect);
        if (enlargement < min_enlargement || !best_child) {
            min_enlargement = enlargement;
            best_child = node->children[i];
        }
    }

    return best_child;
}

// Recursive function to insert a rectangle into the R-tree
static void RTreeInsertRectRecursive(const RTreeRect* rect, int id, struct RTreeNode* node) {
    if (!node) {
        return;
    }

    if (node->num_rects < MAX_RECTS_PER_NODE) {
        // If the node has space, insert the rectangle directly
        node->rects[node->num_rects] = *rect;
        node->num_rects++;
    } else {
        // If the node is full, choose the best child node for insertion
        struct RTreeNode* best_child = choose_best_child(rect, node);
        RTreeInsertRectRecursive(rect, id, best_child);
    }
}

// Search for rectangles within a given rectangle in the R-tree
RTreeList* RTreeSearch(const RTreeRect* rect, const RTree* tree) {
    if (!rect || !tree) {
        return NULL;
    }
    return RTreeSearchRecursive(rect, tree->root);
}

// Helper function to check if two rectangles overlap
static int rect_overlap(const RTreeRect* rect1, const RTreeRect* rect2) {
    if (rect1->min[0] > rect2->max[0] || rect2->min[0] > rect1->max[0]) {
        return 0; // No overlap on X-axis
    }
    if (rect1->min[1] > rect2->max[1] || rect2->min[1] > rect1->max[1]) {
        return 0; // No overlap on Y-axis
    }
    return 1; // Rectangles overlap
}

// Recursive function to search for rectangles within a given rectangle in the R-tree
static RTreeList* RTreeSearchRecursive(const RTreeRect* rect, const struct RTreeNode* node) {
    if (!node) {
        return NULL;
    }

    RTreeList* results = NULL;
    for (int i = 0; i < node->num_rects; i++) {
        // Check if the rectangle overlaps with the search rectangle
        if (rect_overlap(&(node->rects[i]), rect)) {
            // If the node is a leaf node, add the rectangle to the results
            if (!node->children[i]) {
                RTreeList* new_result = malloc(sizeof(RTreeList));
                if (!new_result) {
                    fprintf(stderr, "Failed to allocate memory for R-tree search result.\n");
                    return results; // Return partial results
                }
                new_result->id = node->rects[i].id;
                new_result->next = results;
                results = new_result;
            } else {
                // If the node is not a leaf node, recursively search its children
                RTreeList* child_results = RTreeSearchRecursive(rect, node->children[i]);
                // Merge child results with current results
                RTreeList* temp = child_results;
                while (temp != NULL) {
                    RTreeList* new_result = malloc(sizeof(RTreeList));
                    if (!new_result) {
                        fprintf(stderr, "Failed to allocate memory for R-tree search result.\n");
                        return results; // Return partial results
                    }
                    new_result->id = temp->id;
                    new_result->next = results;
                    results = new_result;
                    temp = temp->next;
                }
                RTreeFreeList(child_results);
            }
        }
    }
    return results;
}

// Function to calculate the distance between two points given their latitude and longitude
float calculate_distance(float lat1, float lon1, float lat2, float lon2) {
    float theta = lon1 - lon2;
    float dist = sin(lat1 * M_PI / 180.0) * sin(lat2 * M_PI / 180.0) +
                 cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) * cos(theta * M_PI / 180.0);
    dist = acos(dist);
    dist = dist * 180.0 / M_PI;
    dist = dist * 60 * 1.1515;
    return dist;
}

// Function to check if a route is within a specified distance from an airport
int is_route_within_distance(Route route, Airport airport, float max_distance) {
    float distance = calculate_distance(airport.latitude, airport.longitude,
                                        route.latitude, route.longitude);
    return distance <= max_distance;
}

// Function to find the minimum distance vertex
int minDistance(float key[], bool mstSet[], int num_vertices) {
    float min = FLT_MAX;
    int min_index;

    for (int v = 0; v < num_vertices; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// Recursive function to print the complete path from source to destination
static void printPath(int parent[], int vertex, Airport* airports) {
    if (parent[vertex] == -1) {
        // Reached the source vertex
        printf("from airport situated at %.1f to airport situated at %.1f ", airports[vertex].latitude, airports[vertex].longitude);
        return;
    }
    // Recursively print the path from source to parent[vertex]
    printPath(parent, parent[vertex], airports);
    // Print the current vertex
    printf("from airport situated at %.1f to airport situated at %.1f ", airports[vertex].latitude, airports[vertex].longitude);
}

// Function to print the optimized routes (minimum spanning tree)
void printOptimizedRoutes(int parent[], int num_vertices, Airport* airports) {
    printf("Optimized Routes:\n");
    for (int i = 1; i < num_vertices; i++) {
        printf("Route %d: ", i);
        printPath(parent, i, airports);
        printf("\n");
    }
}

void dijkstra(struct Graph* graph, int src, Airport* airports[]) {
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

        // Traverse the adjacency list of the current vertex 'u'
        struct EdgeNode* temp = graph->adjList[u].head;
        while (temp != NULL) {
            int v = temp->destination;

            if (minHeap->pos[v] < minHeap->size && dist[u] != DBL_MAX && (dist[u] + temp->weight) < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    // Print optimized routing
    printOptimizedRoutes(parent, V, *airports);
}

void optimize_air_traffic(Airport* airports, int num_airports, Route* routes, int num_routes) {
    // Create graph and add edges
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = num_airports;
    graph->adjList = (struct EdgeList*)malloc(graph->V * sizeof(struct EdgeList));

    for (int i = 0; i < graph->V; ++i) {
        graph->adjList[i].head = NULL;
    }

    for (int i = 0; i < num_airports; ++i) {
        for (int j = i + 1; j < num_airports; ++j) {
            float distance = calculate_distance(airports[i].latitude, airports[i].longitude,
                                                airports[j].latitude, airports[j].longitude);
            if (route_exists(airports[i], airports[j], routes, num_routes) && distance <= 2000) {
                // Add an edge between airports if a direct route exists and the distance is within 2000 miles
                add_edge(&graph->adjList[i], j, distance);
                add_edge(&graph->adjList[j], i, distance);
            }
        }
    }

    // Run Dijkstra's algorithm to find optimized routes
    dijkstra(graph, 0, &airports);

    // Free memory allocated for the graph
    for (int i = 0; i < graph->V; ++i) {
        free_list(graph->adjList[i].head);
    }
    free(graph->adjList);
    free(graph);
}
