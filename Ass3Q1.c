#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 100

int stack[MAX_SIZE];
int top = -1;

bool isFull() {
    return top == MAX_SIZE - 1;
}
bool isEmpty() {
    return top == -1;
}
void push(int value) {
    if (isFull()) {
        return;
    }
    stack[++top] = value;
    printf("Pushed %d onto the stack\n",value);
}
void pop() {
    if (isEmpty()) {
        return;
    }
    printf("Popped %d from the stack\n",stack[top--]);
}
void peek() {
    if (isEmpty()) {
        return;
    }
    printf("%d is the top value",stack[top]);
}
void display() {
    if (isEmpty()) {
        return;
    }
    int i;
    for (i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}
int main() {
    push(6);
    push(7);
    push(8);
    push(5);
    push(3);
    pop(stack);
    push(10);
    pop(stack);
    pop(stack);
    printf("Stack elements:\n");
    display(stack);
    peek(stack);
    return 0;
}
