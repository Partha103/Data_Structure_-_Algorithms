#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int stack1[MAX_SIZE]; 
int stack2[MAX_SIZE]; 
int top1 = -1;        
int top2 = -1;        
void push(int stack[], int *top, int item) {
    if (*top == MAX_SIZE - 1) {
        printf("Stack is full. Cannot push.\n");
        return;
    }
    stack[++(*top)] = item;
}
int pop(int stack[], int *top) {
    if (*top == -1) {
        printf("Stack is empty. Cannot pop.\n");
        return -1;
    }
    return stack[(*top)--];
}
void enqueue(int item) {
    push(stack1, &top1, item);
    printf("%d enqueued.\n", item);
}

int dequeue() {
    if (top1 == -1 && top2 == -1) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    if (top2 == -1) {
        while (top1 != -1) {
            int item = pop(stack1, &top1);
            push(stack2, &top2, item);
        }
    }
    return pop(stack2, &top2);
}
int main() {
    enqueue(1);
    enqueue(2);
    enqueue(3);

    printf("Dequeued: %d\n", dequeue());
    printf("Dequeued: %d\n", dequeue());
    printf("Dequeued: %d\n", dequeue());
    printf("Dequeued: %d\n", dequeue()); 

    return 0;
}