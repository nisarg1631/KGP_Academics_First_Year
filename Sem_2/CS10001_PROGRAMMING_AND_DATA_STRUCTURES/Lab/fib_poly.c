#include <stdio.h>
#include <stdlib.h>

void copy_arr(int from[],int to[],int n){
	int i=0;
	while(i<n){
		to[i]=from[i];
		i++;
	}
}
void add_arr(int from[],int to[],int from_start,int from_end,int to_start){
	while(from_start<=from_end){
		to[to_start]+=from[from_start];
		from_start++;
		to_start++;
	}
}
void zero_arr(int arr[],int n){
	for(int i=0;i<n;i++)
		arr[i]=0;
}

int main(){
	int n;

	printf("n = ");
	scanf("%d",&n);

	int* arr=(int*)calloc(n,sizeof(int));
	int* arr1=(int*)calloc(n,sizeof(int));
	int* arr2=(int*)calloc(n,sizeof(int));

	arr2[0]=1;
	arr1[0]=0;
	arr1[1]=1;

	for(int i=0;i<n-2;i++){
		zero_arr(arr,n);
		add_arr(arr2,arr,0,i,0);
		add_arr(arr1,arr,0,i+1,1);
		copy_arr(arr1,arr2,n);
		copy_arr(arr,arr1,n);
	}

	if(n==0||n==1)
		printf("F_%d(x) = %d\n",n,n);
	else if(n==2)
		printf("F_%d(x) = %dx^%d\n",n,1,1);
	else{
		printf("F_%d(x) = ",n);
		for(int i=n-1;i>=0;i--){
			if(arr[i]!=0){
				if(i==n-1)
					printf("%dx^%d",arr[i],i);
				else if(i==0)
					printf(" + %d\n",arr[i]);
				else
					printf(" + %dx^%d",arr[i],i);
			}
		}
		if(arr[0]==0)
			printf("\n");
	}
	return 0;
}
