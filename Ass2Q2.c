#include <stdio.h>

void transpose(int arr[][100], int n, int m) {
    int transposed[m][n],i,j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            transposed[i][j] = arr[j][i];
        }
    }
    printf("Transpose of the array:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int n, m,i,j;
    printf("Enter the Row number:");
    scanf("%d", &n);
    printf("Enter the column number:");
    scanf("%d", &m);
    int arr[100][100];
    printf("Enter the array elements:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    printf("the original array is :\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    transpose(arr, n, m);
    return 0;
}
