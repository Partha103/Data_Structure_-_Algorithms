#include <stdio.h>
#define MAX_SIZE 100

int stack[MAX_SIZE];
int top = -1;
int i;
int isEmpty() {
    return top == -1;
}
int isFull() {
    return top == MAX_SIZE - 1;
}
void push(int val) {
    if (isFull()) {
        printf("Stack is full. Cannot push %d.\n", val);
    } else {
        top++;
        stack[top] = val;
        printf("%d pushed onto the stack.\n", val);
    }
}
void display() {
    if (isEmpty()) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack elements: \n");
        for (i = top;i>= 0; i--) {
            printf("%d \n", stack[i]);
        }
    }
}
int main() {
    push(1);
    push(2);
    push(3);

    display();


    return 0;
}
