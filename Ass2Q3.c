#include <stdio.h>

typedef struct {
    int row, col, value;
} Element;
void createSparseMatrix(int mat[100][100], int rows, int cols, Element sparseMat[], int *numElements) {
    *numElements = 0;
    int i,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (mat[i][j] != 0) {
                sparseMat[*numElements].row = i;
                sparseMat[*numElements].col = j;
                sparseMat[*numElements].value = mat[i][j];
                (*numElements)++;
            }
        }
    }
}
void displaySparseMatrix(Element sparseMat[], int numElements) {
    printf("Row\tColumn\tValue\n");
    int i;
    for (i = 0; i < numElements; i++) {
        printf("%d\t%d\t%d\n", sparseMat[i].row+1, sparseMat[i].col+1, sparseMat[i].value);
    }
}
int main() {
    int mat[100][100];
    int rows, cols, i, j;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);
    printf("Enter matrix elements:\n");
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    Element sparseMat[100 * 100];
    int numElements;
    createSparseMatrix(mat, rows, cols, sparseMat, &numElements);
    printf("Sparse matrix:\n");
    displaySparseMatrix(sparseMat, numElements);
    return 0;
}
