/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Dynamic memory allocation for 1D integer array (9c)*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *n1, int *n2){
	int temp;
	temp=*n1;
	*n1=*n2;
	*n2=temp;
}

void shiftRight(int *a,int n){
	int *temp=a;
	for(int i=1;i<n;i++){
		swap(a+i,temp);
	}
	*a=*temp;
}

int main(){
	int n;
	printf("Enter number of elements: ");
	scanf("%d",&n);

	int *a=(int *)malloc(n*sizeof(int));
	printf("Enter the %d elements: ",n);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);

	printf("Size of a[] = %lu\n",n*sizeof(int));
	printf("a[] = ");
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");

	for(int i=1;i<=n;i++){
		shiftRight(a,n);
		printf("After %d function calls:\na[] = ",i);
		for(int i=0;i<n;i++)
			printf("%d ",a[i]);
		printf("\n");
	}

	return 0;
}
