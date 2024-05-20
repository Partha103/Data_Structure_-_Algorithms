#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
int queue[MAX_SIZE];
int front = -1, rear = -1;

void enqueue(int item) {
    if (rear == MAX_SIZE - 1) {
        return;
    } else {
        if (front == -1)
            front = 0;
        rear++;
        queue[rear] = item;
        printf("Inserted: %d\n", item);
    }
}
int dequeue() {
    int item;
    if (front == -1) {
        return -1;
    } else {
        item = queue[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front++;
        }
        printf("Deleted: %d\n", item);
        return item;
    }
}
void traverse() {
    if (front == -1) {
        printf("Queue is empty.\n");
    } else {
        printf("Queue elements: \n");
        for (int i = front; i <= rear; i++) {
            printf("%d \n", queue[i]);
        }
        printf("\n");
    }
}
int main() {
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);
    traverse();
    dequeue();
    dequeue();
    traverse();
    return 0;
}