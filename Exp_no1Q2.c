#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binary_search_recursive(int arr[], int low, int high, int target) {
    if (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) {
            printf("Target found: %d\n", mid);
            return mid;
        } else if (arr[mid] < target) {
            return binary_search_recursive(arr, mid + 1, high, target);
        } else {
            return binary_search_recursive(arr, low, mid - 1, target);
        }
    } else {
        printf("Target not found!!!\n");
        return -1;
    }
}

void measure_execution_time_and_memory(int result, clock_t start_time) {
    clock_t end_time = clock();
    double execution_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    int memory_usage = sizeof(result) + sizeof(start_time) + sizeof(end_time);

    printf("Execution Time: %f seconds\n", execution_time);
    printf("Memory Usage: %d bytes\n", memory_usage);
}

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the array elemants: ");
    for(int i = 0; i<size; i++){
        scanf("%d", &arr[i]);
    }
    int target;
    printf("Enter the target: ");
    scanf("%d", &target);

    clock_t start_time_recursive = clock();
    int result_recursive = binary_search_recursive(arr, 0, size - 1, target);
    measure_execution_time_and_memory(result_recursive, start_time_recursive);

    return 0;
}