#include <stdio.h>
#include <stdlib.h>

typedef struct Activity {
    int id;
    int start;
    int finish;
} Activity;

// Structure to represent a node in the priority queue
typedef struct Node {
    Activity data;
    struct Node* next;
} Node;

// Function to create a new node
Node* newNode(Activity data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Priority queue (min heap) implementation
typedef struct PriorityQueue {
    Node* head;
} PriorityQueue;

// Function to initialize an empty priority queue
PriorityQueue* initPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    return pq;
}

// Function to insert an activity into the priority queue
void insert(PriorityQueue* pq, Activity activity) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = activity;
    newNode->next = pq->head;
    pq->head = newNode;
}

// Function to remove and return the activity with the smallest finish time from the priority queue
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

// Recursive function to find the maximum number of non-conflicting activities
void selectActivitiesRecursive(PriorityQueue* pq, int lastFinishTime) {
    if (pq->head == NULL) // Base case: no more activities
        return;

    // Select the next activity
    Activity selectedActivity = extractMin(pq);

    // If the start time of the selected activity is after the finish time of the last activity
    // Add it to the selected activities list and recursively select activities from the remaining ones
    if (selectedActivity.start >= lastFinishTime) {
        printf("Selected Activity: %d\n", selectedActivity.id);
        selectActivitiesRecursive(pq, selectedActivity.finish);
    } else {
        // Skip this activity and move to the next one
        selectActivitiesRecursive(pq, lastFinishTime);
    }
}

int main() {
    PriorityQueue* pq = initPriorityQueue();

    // Insert activities from the table
    Activity activities[] = {
        {1, 1, 4}, {2, 3, 5}, {3, 0, 6}, {4, 5, 7}, {5, 3, 9},
        {6, 5, 9}, {7, 6, 10}, {8, 8, 11}, {9, 8, 12}, {10, 2, 14},
        {11, 12, 16}, {12, 9, 13}, {13, 7, 13}, {14, 3, 8}, {15, 5, 8},
        {16, 14, 16}, {17, 15, 16}, {18, 10, 16}, {19, 13, 15}
    };
    int numActivities = sizeof(activities) / sizeof(activities[0]);
    for (int i = 0; i < numActivities; i++)
        insert(pq, activities[i]);

    printf("Maximum number of non-conflicting activities:\n");
    selectActivitiesRecursive(pq, 0);

    return 0;
}