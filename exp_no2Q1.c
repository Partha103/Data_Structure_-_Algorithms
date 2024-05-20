#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 1000

typedef struct {
    int priority;
    int data;
} Node;

typedef struct {
    Node heap[MAX_SIZE];
    int size;
} MinPriorityQueue;

MinPriorityQueue* createMinPriorityQueue() {
    MinPriorityQueue* pq = (MinPriorityQueue*)malloc(sizeof(MinPriorityQueue));
    pq->size = 0;
    return pq;
}

bool isFull(MinPriorityQueue* pq) {
    return pq->size >= MAX_SIZE;
}

bool isEmpty(MinPriorityQueue* pq) {
    return pq->size == 0;
}

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinPriorityQueue* pq, int index) {
    while (index > 0 && pq->heap[index].priority < pq->heap[(index - 1) / 2].priority) {
        swap(&pq->heap[index], &pq->heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void insert(MinPriorityQueue* pq, int priority, int data) {
    if (isFull(pq)) {
        printf("Overflow:\n");
        return;
    }
    pq->heap[pq->size].priority = priority;
    pq->heap[pq->size].data = data;
    pq->size++;
    heapifyUp(pq, pq->size - 1);
}

void heapifyDown(MinPriorityQueue* pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->heap[left].priority < pq->heap[smallest].priority)
        smallest = left;
    if (right < pq->size && pq->heap[right].priority < pq->heap[smallest].priority)
        smallest = right;

    if (smallest != index) {
        swap(&pq->heap[index], &pq->heap[smallest]);
        heapifyDown(pq, smallest);
    }
}

Node deleteMin(MinPriorityQueue* pq) {
    Node min = pq->heap[0];
    pq->size--;
    pq->heap[0] = pq->heap[pq->size];
    heapifyDown(pq, 0);
    return min;
}

void display(MinPriorityQueue* pq) {
    printf("Priority Queue:\n");
    for (int i = 0; i < pq->size; i++) {
        printf("(%d, %d) ", pq->heap[i].priority, pq->heap[i].data);
    }
    printf("\n");
}

int main() {
    MinPriorityQueue* pq = createMinPriorityQueue();

    FILE* fp = fopen("text.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int priority, data;
    while (fscanf(fp, "%d %d", &priority, &data) != EOF) {
        insert(pq, priority, data);
    }
    fclose(fp);

    display(pq);

    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    while (!isEmpty(pq)) {
        Node min = deleteMin(pq);
        printf("Deleted: (%d, %d)\n", min.priority, min.data);
        fprintf(fp, "Deleted: (%d, %d)\n", min.priority, min.data);
    }
    fclose(fp);

    free(pq);

    return 0;
}
