#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binary_search_iterative(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) {
            printf("Target found at %dth position\n", mid);
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    printf("Target not found!!!\n");
    return -1;
}

void measure_execution_time_and_memory(int result, clock_t start_time) {
    clock_t end_time = clock();
    double execution_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    
    int memory_usage = sizeof(result) * 2 + sizeof(start_time) + sizeof(end_time);

    printf("Execution Time: %f seconds\n", execution_time);
    printf("Memory Usage: %d bytes\n", memory_usage);
}

int main() {
    int size;
    printf("Enter the size of the array : ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the array elements : ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    int target;
    printf("Enter the target: ");0
    scanf("%d", &target);

    clock_t start_time_iterative = clock();
    int result_iterative = binary_search_iterative(arr, size, target);
    measure_execution_time_and_memory(result_iterative, start_time_iterative);

    return 0;
}