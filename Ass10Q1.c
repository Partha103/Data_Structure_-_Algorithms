#include <stdio.h>

int leftOcc(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1; 
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int countOccurrences(int arr[], int n, int target) {
    int left = leftOcc(arr, n, target);
    if (left == -1) {
        return 0;
    }
    int right = left;
    while (right < n && arr[right] == target) {
        right++;
    }

    return right - left;
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the array elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int target;
    printf("Enter the target: ");
    scanf("%d", &target);

    int count = countOccurrences(arr, n, target);

    if (count > 0) {
        printf("%d %d %d\n", leftOcc(arr, n, target), leftOcc(arr, n, target) + count - 1, count);
    } else {
        printf("-1\n");
    }

    return 0;
}
