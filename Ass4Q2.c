#include <stdio.h>

#define MAX_SIZE 5
int circularQueue[MAX_SIZE];
int front = -1, rear = -1;
int isEmpty() {
    return (front == -1 && rear == -1);
}
int isFull() {
    return ((rear + 1) % MAX_SIZE == front);
}
void CQINSERT(int item) {
    if (isFull()) {
        printf("Circular Queue is full. Cannot insert.\n");
        return;
    } else {
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % MAX_SIZE;
        }
        circularQueue[rear] = item;
        printf("Inserted in a Circular Queue: %d\n", item);
    }
}
void CQDELETE() {
    if (isEmpty()) {
        printf("Circular Queue is empty. Cannot delete.\n");
        return;
    } else {
        int deletedItem = circularQueue[front];
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % MAX_SIZE;
        }
        printf("Deleted from a Circular Queue: %d\n", deletedItem);
    }
}
int main() {
    CQINSERT(1);
    CQINSERT(2);
    CQINSERT(3);

    CQDELETE();
    CQDELETE();
    CQDELETE();
    CQDELETE();

    return 0;
}