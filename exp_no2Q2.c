#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

void insert(Node** root, int data);
void heapify(Node* root);
void heapSort(Node* root);
void printInOrder(Node* root);
void freeTree(Node* root);

int main() {
    Node* root = NULL;

    FILE* fp = fopen("text.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    int data;
    while (fscanf(fp, "%d", &data) != EOF) {
        insert(&root, data);
    }
    fclose(fp);

    printf("Input data:\n");
    printInOrder(root);
    printf("\n");

    clock_t start = clock();

    heapSort(root);

    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nExecution time: %f seconds\n", cpu_time_used);

    printf("\nSorted data:\n");
    printInOrder(root);
    printf("\n");

    freeTree(root);

    return 0;
}

void insert(Node** root, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;

    if (*root == NULL) {
        *root = newNode;
    } else {
        Node* temp = *root;
        while (temp->left != NULL && temp->right != NULL) {
            temp = temp->left;
        }

        if (temp->left == NULL) {
            temp->left = newNode;
        } else {
            temp->right = newNode;
        }
    }
}

void heapify(Node* root) {
    if (root == NULL) {
        return;
    }

    Node* largest = root;
    Node* left = root->left;
    Node* right = root->right;

    if (left != NULL && left->data > largest->data) {
        largest = left;
    }
    if (right != NULL && right->data > largest->data) {
        largest = right;
    }

    if (largest != root) {
        int temp = root->data;
        root->data = largest->data;
        largest->data = temp;
        heapify(largest);
    }
}

void heapSort(Node* root) {
    if (root == NULL) {
        printf("Underflow: Binary tree is empty!\n");
        return;
    }

    heapify(root);

    if (root->left != NULL) {
        heapSort(root->left);
    }
    if (root->right != NULL) {
        heapSort(root->right);
    }
}

void printInOrder(Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->data);
        printInOrder(root->right);
    }
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
