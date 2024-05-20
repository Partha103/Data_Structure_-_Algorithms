#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

int matrixMultiplication(int n, int a[]);
int min(int a, int b);

int main() {
    int a[] = {15,12,8,20,6,15,20};
    int n = sizeof(a)/sizeof(a[0]);

    int result = matrixMultiplication(n, a);
    printf("Minimum Operations: %d", result);

    return 0;
}

int matrixMultiplication(int n, int a[]) {
    int dp[n][n];
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<n; j++) {
            dp[i][j] = 0;
        }
    }

    for(int len = 2; len<n; len++) {
        for(int row = 0, col = len; row<n-len; row++, col++) {
            dp[row][col] = INT_MAX;
            for(int k = row+1; k<col; k++) {
                dp[row][col] = min(dp[row][col], (dp[row][k] + dp[k][col]+ a[row]*a[k]*a[col]));
            }
        }
    }
    return dp[0][n-1];
}

int min(int a, int b) {
    if(a < b) {
        return a;
    }else{
        return b;
    }
}