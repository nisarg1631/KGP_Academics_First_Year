/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 13(c)*/

#include <stdio.h>
#include <stdlib.h>

int **create_2d_array(int rows, int cols){
	int **arr;
	arr=(int **)malloc(rows*sizeof(int *));
	for(int i=0;i<rows;i++)
		arr[i]=(int *)malloc(cols*sizeof(int));
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			arr[i][j]=0;
	return arr;
}

int main(){
	int n;

	printf("Enter n: ");
	scanf("%d",&n);
	printf("\n");

	int **A=create_2d_array(n,n), **B=create_2d_array(n,n);

	for(int i=0;i<n;i++){
		A[i][i]=1, B[i][i]=1;
		int j;
		printf("Enter friends of %d (between 0 and %d, enter -1 to terminate): ",i,n-1);
		scanf("%d",&j);
		while(j!=-1){
			if(j>=0&&j<=(n-1)){
				A[i][j]=1, A[j][i]=1;
				B[i][j]=1, B[j][i]=1;
			}
			scanf("%d",&j);
		}
	}
	printf("\n");
	
	printf("A =\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%d ",A[i][j]);
		printf("\n");
	}
	printf("\n");

	int *best_students=(int *)malloc(n*sizeof(int)), count=0, max=0, temp;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(A[i][j]){
				for(int k=0;k<n;k++){
					if(A[j][k])
						B[i][k]=1;
				}
			}
		}
		temp=0;
		for(int j=0;j<n;j++){
			if(B[i][j])
				temp++;
		}
		if(temp>max){
			max=temp;
			count=0;
			best_students[count++]=i;
		}
		else if(temp==max)
			best_students[count++]=i;
	}

	printf("B =\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%d ",B[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("Best students =");
	for(int i=0;i<count;i++){
		if(i!=count-1)
			printf(" %d,",best_students[i]);
		else
			printf(" %d",best_students[i]);
	}
	printf("\n");

	return 0;
}