#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int low, int mid, int high, int *numComparisons) {
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        (*numComparisons)++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int low, int high, int *numComparisons) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid, numComparisons);
        mergeSort(arr, mid + 1, high, numComparisons);

        merge(arr, low, mid, high, numComparisons);
    }
}

int main() {
    FILE *inputFile = fopen("text.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    int n;
    fscanf(inputFile, "%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d", &arr[i]);
    }
    fclose(inputFile);

    clock_t start_time = clock();

    int numComparisons = 0;
    mergeSort(arr, 0, n - 1, &numComparisons);

    clock_t end_time = clock();

    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%d ", arr[i]);
    }
    fprintf(outputFile, "\n");
    fprintf(outputFile, "Number of comparisons: %d\n", numComparisons);
    fprintf(outputFile, "Execution time: %f seconds\n", execution_time);

    fclose(outputFile);
    free(arr);

    return 0;
}