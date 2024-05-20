#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}
void insertAtEnd(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
struct Node* searchElement(struct Node* head, int target) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == target) {
            return current;
        }
        current = current->next;
    }
    return NULL; 
}
int main() {
    struct Node* head = NULL;
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 40);
    insertAtEnd(&head, 50);

    printf("Linked List: ");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    int target = 30;
    struct Node* result = searchElement(head, target);

    if (result != NULL) {
        printf("Element %d found at address %p\n", target, (void*)result);
    } else {
        printf("Element %d not found in the linked list\n", target);
    }

    // Free memory (optional)
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
