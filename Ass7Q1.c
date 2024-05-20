#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct TreeNode {
    char day[30];
    struct TreeNode* left;
    struct TreeNode* right;
};
struct TreeNode* createNode(char* day) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    strcpy(newNode->day, day);
    newNode->left = newNode->right = NULL;
    return newNode;
}
struct TreeNode* insert(struct TreeNode* root, char* day) {
    if (root == NULL) {
        return createNode(day);
    }
    if (strcmp(day, root->day) < 0) {
        root->left = insert(root->left, day);
    } else if (strcmp(day, root->day) > 0) {
        root->right = insert(root->right, day);
    }
    return root;
}
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s\n", root->day);
        inorderTraversal(root->right);
    }
}
int main() {
    struct TreeNode* root = NULL;
    root = insert(root, "Sunday");
    root = insert(root, "Monday");
    root = insert(root, "Tuesday");
    root = insert(root, "Wednesday");
    root = insert(root, "Thursday");
    root = insert(root, "Friday");
    root = insert(root, "Saturday");
    printf("Days of the week in alphabetical order:\n");
    inorderTraversal(root);
    free(root);
    return 0;
}
