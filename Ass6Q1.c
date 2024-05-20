#include <stdio.h>                               
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAtPosition(struct Node** headRef, int data, int position) {
    if (position < 1) {
        printf("Invalid position. Position should be greater than or equal to 1.\n");
        return;
    }

    struct Node* newNode = createNode(data);

    if (position == 1) {
        newNode->next = *headRef;
        if (*headRef != NULL) {
            (*headRef)->prev = newNode;
        }
        *headRef = newNode;
    } else {
        struct Node* current = *headRef;
        int currentPosition = 1;

        while (currentPosition < position - 1 && current != NULL) {
            current = current->next;
            currentPosition++;
        }

        if (current == NULL && currentPosition < position - 1) {
            printf("Position exceeds the length of the list. Node not inserted.\n");
        } else {
            newNode->next = current->next;
            if (current->next != NULL) {
                current->next->prev = newNode;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }
}

void printList(struct Node* head) {
    printf("Doubly Linked List: ");
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int data, position;

    printf("Enter the number of nodes you want to create: ");
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        insertAtPosition(&head, data, i + 1);
    }

    printList(head);

    printf("Enter the data you want to insert: ");
    scanf("%d", &data);
    printf("Enter the position at which you want to insert: ");
    scanf("%d", &position);

    insertAtPosition(&head, data, position);

    printList(head);

    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}