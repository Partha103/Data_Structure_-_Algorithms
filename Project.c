#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
};

struct FloatNode {
    float data;
    struct FloatNode* next;
};

struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
};

void printIntArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printFloatArray(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

void printCharArray(char arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%c ", arr[i]);
    }
    printf("\n");
}

void printStringArray(char* arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

void insertionSortIntArray(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

void insertionSortFloatArray(float arr[], int size) {
    for (int i = 1; i < size; i++) {
        float key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

void insertionSortCharArray(char arr[], int size) {
    for (int i = 1; i < size; i++) {
        char key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

void insertionSortStringArray(char* arr[], int size) {
    for (int i = 1; i < size; i++) {
        char* key = arr[i];
        int j = i - 1;

        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

void printIntLinkedList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void printFloatLinkedList(struct FloatNode* head) {
    while (head != NULL) {
        printf("%.2f -> ", head->data);
        head = head->next;
    }
    printf("null\n");
}

void printDoublyLinkedList(struct DNode* head) {
    while (head != NULL) {
        printf("null<- %d <-> ", head->data);
        head = head->next;
    }
    printf("null\n");
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct FloatNode* createFloatNode(float data) {
    struct FloatNode* newNode = (struct FloatNode*)malloc(sizeof(struct FloatNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct DNode* createDNode(int data) {
    struct DNode* newNode = (struct DNode*)malloc(sizeof(struct DNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertionSortLinkedList(struct Node** headRef) {
    struct Node* sorted = NULL;
    struct Node* current = *headRef;

    while (current != NULL) {
        struct Node* next = current->next;

        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    *headRef = sorted;
}

void insertionSortFloatLinkedList(struct FloatNode** headRef) {
    struct FloatNode* sorted = NULL;
    struct FloatNode* current = *headRef;

    while (current != NULL) {
        struct FloatNode* next = current->next;

        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct FloatNode* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    *headRef = sorted;
}

void insertionSortDoublyLinkedList(struct DNode** headRef) {
    struct DNode* sorted = NULL;
    struct DNode* current = *headRef;

    while (current != NULL) {
        struct DNode* next = current->next;

        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            current->prev = NULL;
            if (sorted != NULL) {
                sorted->prev = current;
            }
            sorted = current;
        } else {
            struct DNode* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            if (temp->next != NULL) {
                temp->next->prev = current;
            }
            temp->next = current;
            current->prev = temp;
        }

        current = next;
    }

    *headRef = sorted;
}

int main() {
    int intArray[100];
    float floatArray[100];
    char charArray[100];
    char* stringArray[100];
    struct Node* intLinkedList = NULL;
    struct FloatNode* floatLinkedList = NULL;
    struct DNode* intDoublyLinkedList = NULL;

    int intArraySize, floatArraySize, charArraySize, stringArraySize;

    printf("Enter the number of elements in the integer array: ");
    scanf("%d", &intArraySize);
    printf("Enter the elements of the integer array: ");
    for (int i = 0; i < intArraySize; i++) {
        scanf("%d", &intArray[i]);
    }
    
    printf("Original Integer Array: ");
    printIntArray(intArray, intArraySize);
    insertionSortIntArray(intArray, intArraySize);
    printf("Sorted Integer Array: ");
    printIntArray(intArray, intArraySize);

    printf("Enter the number of elements in the float array: ");
    scanf("%d", &floatArraySize);
    printf("Enter the elements of the float array: ");
    for (int i = 0; i < floatArraySize; i++) {
        scanf("%f", &floatArray[i]);
    }

    printf("Original Float Array: ");
    printFloatArray(floatArray, floatArraySize);
    insertionSortFloatArray(floatArray, floatArraySize);
    printf("Sorted Float Array: ");
    printFloatArray(floatArray, floatArraySize);

    printf("Enter the number of elements in the character array: ");
    scanf("%d", &charArraySize);
    printf("Enter the elements of the character array: ");
    for (int i = 0; i < charArraySize; i++) {
        scanf(" %c", &charArray[i]);
    }

    printf("Original Character Array: ");
    printCharArray(charArray, charArraySize);
    insertionSortCharArray(charArray, charArraySize);
    printf("Sorted Character Array: ");
    printCharArray(charArray, charArraySize);

    printf("Enter the number of strings in the string array: ");
    scanf("%d", &stringArraySize);
    printf("Enter the strings in the string array:\n");
    for (int i = 0; i < stringArraySize; i++) {
        stringArray[i] = (char*)malloc(100 * sizeof(char));
        scanf("%s", stringArray[i]);
    }

    printf("Original String Array: ");
    printStringArray(stringArray, stringArraySize);
    insertionSortStringArray(stringArray, stringArraySize);
    printf("Sorted String Array: ");
    printStringArray(stringArray, stringArraySize);

    printf("Enter the number of elements in the integer linked list: ");
    scanf("%d", &intArraySize);
    printf("Enter the elements of the integer linked list: ");
    for (int i = 0; i < intArraySize; i++) {
        int data;
        scanf("%d", &data);
        struct Node* newNode = createNode(data);
        newNode->next = intLinkedList;
        intLinkedList = newNode;
    }

    printf("Original Integer Linked List: ");
    printIntLinkedList(intLinkedList);
    insertionSortLinkedList(&intLinkedList);
    printf("Sorted Integer Linked List: ");
    printIntLinkedList(intLinkedList);

    printf("Enter the number of elements in the float linked list: ");
    scanf("%d", &floatArraySize);
    printf("Enter the elements of the float linked list: ");
    for (int i = 0; i < floatArraySize; i++) {
        float data;
        scanf("%f", &data);
        struct FloatNode* newNode = createFloatNode(data);
        newNode->next = floatLinkedList;
        floatLinkedList = newNode;
    }

    printf("Original Float Linked List: ");
    printFloatLinkedList(floatLinkedList);
    insertionSortFloatLinkedList(&floatLinkedList);
    printf("Sorted Float Linked List: ");
    printFloatLinkedList(floatLinkedList);

    printf("Enter the number of elements in the integer doubly linked list: ");
    scanf("%d", &intArraySize);
    printf("Enter the elements of the integer doubly linked list: ");
    for (int i = 0; i < intArraySize; i++) {
        int data;
        scanf("%d", &data);
        struct DNode* newNode = createDNode(data);
        if (intDoublyLinkedList == NULL) {
            intDoublyLinkedList = newNode;
        } else {
            struct DNode* current = intDoublyLinkedList;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }

    printf("Original Integer Doubly Linked List: ");
    printDoublyLinkedList(intDoublyLinkedList);
    insertionSortDoublyLinkedList(&intDoublyLinkedList);
    printf("Sorted Integer Doubly Linked List: ");
    printDoublyLinkedList(intDoublyLinkedList);

    return 0;
}