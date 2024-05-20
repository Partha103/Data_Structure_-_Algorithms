#include<stdio.h>

int BinarySearch(int arr[],int size, int tar){
    int frst=0;
    int end= size-1;
    
    while(frst<=end){
        int mid = (frst+end)/2;
        if(arr[mid]==tar){
            return mid;
        }
        else if(arr[mid]>tar){
            end= mid-1;
        }
        else{
            frst= mid+1;
        }
    }
    return -1;
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
    int index = BinarySearch(arr,size,tar);
    if(index==-1){
        printf("Not found");
    }
    else{
        printf("The element is found at index %d",index);
    }
    return 0;
}