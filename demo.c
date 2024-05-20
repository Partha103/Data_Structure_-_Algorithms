#include<stdio.h>

int linearSearch(int arr[],int size, int tar){
    if(arr[size-1]==tar){
        return size-1;
    }
    else{
        linearSearch(arr,size-1,tar);
    }
}

int main(){
    int size;
    scanf("%d",&size);
    printf("Enter the array elements:");
    int arr[size];
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }
    int tar;
    printf("Enter the target:");
    scanf("%d",&tar);
    int index = linearSearch(arr,size,tar);
    if(index==-1){
        printf("Not found");
    }
    else{
        printf("%d",index);
    }
    return 0;
}