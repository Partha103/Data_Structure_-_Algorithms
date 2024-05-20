#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
void insertAfter(struct Node* prevNode, int newData) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL\n");
        return;
    }
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("null\n");
}
int main(){
    struct Node* head = NULL;  
    struct Node* current = NULL;
    int data;
    char choice;

    do {
        printf("Enter data for a new node: ");
        scanf("%d", &data);

        struct Node* newNode = malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;  
            current = head; 
        } else {
            current->next = newNode;
            current = newNode;
        }
        printf("Do you want to add another node? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    printf("Linked List: ");
    printList(head);

    int insertData, afterData;
    printf("Enter data to insert: ");
    scanf("%d", &insertData);
    printf("Enter data after which to insert: ");
    scanf("%d", &afterData);
    current = head;
    while (current != NULL) {
        if (current->data == afterData) {
            insertAfter(current, insertData);
            break;
        }
        current = current->next;
    }

    printf("Updated Linked List: ");
    printList(head);

    return 0;
}