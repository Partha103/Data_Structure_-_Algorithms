#include <stdio.h>
#include <string.h>

void swap(char *xp, char *yp) {
    char temp[100];
    strcpy(temp, xp);
    strcpy(xp, yp);
    strcpy(yp, temp);
}

void selectionSort(char arr[][100], int n) {
    int i, j, min_idx;
    int pass = 0;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (strlen(arr[j]) < strlen(arr[min_idx])) {
                min_idx = j;
            }
            pass++;
        }
        swap(arr[min_idx], arr[i]);
    }
    printf("Total passes required: %d\n", pass);
}

int main() {
    int N;
    printf("Enter the number of strings (10 <= N <= 20): ");
    scanf("%d", &N);
    if (N < 10 || N > 20) {
        printf("Invalid input range.\n");
        return 0;
    }

    char arr[N][100];
    printf("Enter %d strings:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%s", arr[i]);
    }

    selectionSort(arr, N);

    printf("Sorted strings by length:\n");
    for (int i = 0; i < N; i++) {
        printf("{%s}-%ld\n", arr[i], strlen(arr[i]));
    }

    return 0;
}