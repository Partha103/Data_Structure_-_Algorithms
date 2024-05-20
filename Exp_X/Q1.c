#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int *x;
int moves = 0;

bool place(int k, int i) {
    for (int j = 1; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
            return false;
        }
    }
    return true;
}

void printSolution(int n) {
    static bool solution_found = false;  // Flag to track if solution has been found
    if (!solution_found) {  // Only print the solution once
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (x[i] == j) {
                    printf("1 ");
                } else {
                    printf("0 ");
                }
            }
            printf("\n");
        }
        solution_found = true;  // Update flag to indicate solution has been found
    }
}

void NQueens(int k, int n, bool *solution_exists) {
    for (int i = 1; i <= n; i++) {
        if (place(k, i)) {
            x[k] = i;
            if (k == n) {
                printSolution(n);
                *solution_exists = true; // Update solution flag
            } else {
                moves++;
                NQueens(k + 1, n, solution_exists);
            }
        }
    }
}

int main() {
    int n;
    clock_t start, end;
    double cpu_time_used;
    bool solution_exists = false;

    printf("Enter the number of queens: ");
    scanf("%d", &n);

    x = (int *)malloc((n + 1) * sizeof(int));

    start = clock();
    NQueens(1, n, &solution_exists);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (!solution_exists) {
        printf("No solution exists.\n");
    } else {
        printf("Time taken: %f seconds\n", cpu_time_used);
        printf("Number of moves: %d\n", moves);
    }

    free(x);
    return 0;
}