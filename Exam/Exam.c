#include <stdio.h>
#include <stdlib.h>

typedef struct Activity {
    int id;
    int start;
    int finish;
} Activity;

typedef struct Node {
    Activity data;
    struct Node* next;
} Node;

Node* newNode(Activity data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

typedef struct PriorityQueue {
    Node* head;
} PriorityQueue;

PriorityQueue* initPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    return pq;
}

void insert(PriorityQueue* pq, Activity activity) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = activity;
    newNode->next = pq->head;
    pq->head = newNode;
}

Activity extractMin(PriorityQueue* pq) {
    if (pq->head == NULL) {
        printf("Priority queue is empty\n");
        exit(1);
    }

    Node* prev = NULL;
    Node* current = pq->head;
    Node* minNode = pq->head;
    Node* prevMinNode = NULL;

    while (current != NULL) {
        if (current->data.finish < minNode->data.finish) {
            minNode = current;
            prevMinNode = prev;
        }
        prev = current;
        current = current->next;
    }

    if (prevMinNode == NULL)
        pq->head = minNode->next;
    else
        prevMinNode->next = minNode->next;

    Activity minActivity = minNode->data;
    free(minNode);
    return minActivity;
}

void selectActivitiesRecursive(PriorityQueue* pq, int lastFinishTime) {
    if (pq->head == NULL)
        return;

    Activity selectedActivity = extractMin(pq);

    if (selectedActivity.start >= lastFinishTime) {
        printf("Selected Activity: %d\n", selectedActivity.id);
        selectActivitiesRecursive(pq, selectedActivity.finish);
    } else {
        selectActivitiesRecursive(pq, lastFinishTime);
    }
}

int main() {
    PriorityQueue* pq = initPriorityQueue();

    FILE *file = fopen("activities.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int id, start, finish;
    while (fscanf(file, "%d %d %d", &id, &start, &finish) == 3) {
        Activity activity = {id, start, finish};
        insert(pq, activity);
    }
    fclose(file);

    printf("Maximum number of non-conflicting activities:\n");
    selectActivitiesRecursive(pq, 0);

    return 0;
}
