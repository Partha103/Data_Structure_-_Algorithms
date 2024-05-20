#include <stdio.h>
#include <math.h>

float calculate_mean(float arr[], int size) {
    int sum = 0, i;
    for (i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (float)sum / size;
}

float calculate_std_dev(float arr[], int size, float mean) {
    float sum_of_squared_diff = 0;
    int i; 
    for (i = 0; i < size; i++) {
        sum_of_squared_diff += pow(arr[i] - mean, 2);
    }
    return sqrt(sum_of_squared_diff / size);
}

int main() {
    int size, i;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    float data_array[size];

    printf("Enter the array:\n");
    for (i = 0; i < size; i++) {
        scanf("%f", &data_array[i]);
    }

    float mean = calculate_mean(data_array, size);
    float std_dev = calculate_std_dev(data_array, size, mean);

    printf("Mean: %.2f\n", mean);
    printf("Standard Deviation: %.2f\n", std_dev);

    return 0;
}