#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high, int *numSwaps) {
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
            (*numSwaps)++;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    (*numSwaps)++;
    return (i + 1);
}

void quickSort(int arr[], int low, int high, int *numSwaps) {
    if (low < high) {
        int pi = partition(arr, low, high, numSwaps);
        quickSort(arr, low, pi - 1, numSwaps);
        quickSort(arr, pi + 1, high, numSwaps);
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

    int numSwaps = 0;
    quickSort(arr, 0, n - 1, &numSwaps);

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

    fprintf(outputFile, "Number of swaps: %d\n", numSwaps);
    fprintf(outputFile, "Execution time: %f seconds\n", execution_time);

    fclose(outputFile);
    free(arr);

    return 0;
}