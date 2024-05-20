#include<stdio.h>
#include<stdbool.h>
#include<math.h>
bool IsPrime(int n);
int main(){
	int n;
	
	for(n=0;n<200;n++){
		if(IsPrime(n)==true){
			printf("%d \n",n);
		}
	}
	return 0;
}
bool IsPrime(int n){
	int i;
	bool prime=true;
	for(i=2;i<=n/2;i++){
		if(n%i==0){
			prime= false;
			break;
		}
	}
	return prime;
}
