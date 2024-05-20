#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

double find_median(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);

    if (n % 2 == 1) {
        return arr[n / 2];
    } else {
        int mid1 = arr[(n / 2) - 1];
        int mid2 = arr[n / 2];
        return (double)(mid1 + mid2) / 2.0;
    }
}

int main() {
    int n,i;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    double median = find_median(arr, n);
    printf("Median: %.2f\n", median);

    return 0;
}
