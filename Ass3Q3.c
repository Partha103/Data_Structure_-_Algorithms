#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LENGTH 100

char stack[MAX_LENGTH];
int top = -1;
int i;
bool isFull() {
    return top == MAX_LENGTH - 1;
}
bool isEmpty() {
    return top == -1;
}
void push(char c) {
    if (isFull()) {
        printf("Stack is full. Cannot push %c\n", c);
        return;
    }
    stack[++top] = c;
}
char pop() {
    if (isEmpty()) {
        printf("Stack is empty. Cannot pop.\n");
        return;
    }
    return stack[top--];
}
void reverseString(char *input) {
    int length = strlen(input);
    for (i = 0; i < length; i++) {
        push(input[i]);
    }
    for (i = 0; i < length; i++) {
        input[i] = pop();
    }
}
int main() {
    char input[MAX_LENGTH];
    printf("Enter a string: ");
    scanf("%s", input);
    reverseString(input);
    printf("Reversed string: %s\n", input);
    return 0;
}
