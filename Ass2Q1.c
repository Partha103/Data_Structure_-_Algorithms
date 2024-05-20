#include<stdio.h>

int main(){
	int n,m,i,j;
	printf("Enter the Row number:");
	scanf("%d",&n);
	printf("Enter the column number:");
	scanf("%d",&m);
	int arr[n][m];
	printf("Enter the array elements:\n");
	int sum = 0;
	for(i = 0;i< n;i++){
		for(j = 0;j<m;j++){
			scanf("%d",&arr[i][j]);
			sum += arr[i][j];
		}
	}
	printf("\nYour matrix is :\n");
	for(i = 0;i< n;i++){
		for(j = 0;j<m;j++){
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
	printf("\nThe sum of all elements of the array is %d",sum);
}
