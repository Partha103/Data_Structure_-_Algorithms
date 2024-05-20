#include <stdio.h>

int main()
{
    int n, m;
    printf("Enter the size of the first array: ");
    scanf("%d", &n);
    int arr1[n];
    printf("Enter the array1 elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr1[i]);
    }
    printf("Enter the size of the second array: ");
    scanf("%d", &m);
    int arr2[m];
    printf("Enter the array2 elements: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &arr2[i]);
    }
    if(m == n){
        printf("There are no missing elements.");
        return 0;
    }
    int missingElements[m-n];
    int ar1 = 0;
    int ar2 = 0;
    int it = 0;
    while (ar1 < n && ar2 < m)
    {
        if(arr1[ar1] != arr2[ar2]){
            missingElements[it] = arr2[ar2];
            it++;
            ar2++;
        }else{
            ar1++;
            ar2++;
        }
    }

    printf("The missing elements are: ");
    for (int i = 0; i < m-n; i++)
    {
        printf("%d ", missingElements[i]);
    }
    printf("\n");

    return 0;
}
