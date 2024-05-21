/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Dynamic memory allocation for 2D integer array (9f)*/

#include <stdio.h>
#include <stdlib.h>

int **create_2d_array(int rows, int cols){
	int **arr;
	arr=(int **)malloc(rows*sizeof(int *));
	for(int i=0;i<rows;i++)
		arr[i]=(int *)malloc(cols*sizeof(int));
	return arr;
}

int check(int **arr, int rows, int cols, int i, int j){
	int flag1=1,flag2=1;
	for(int z=0;z<cols;z++){
		if(z!=j){
			if(arr[i][z]>=arr[i][j])
					flag1=0;
			if(arr[i][z]<=arr[i][j])
					flag2=0;
		}
	}
	if(flag1==0&&flag2==0)
		return 0;
	else if(flag1==1){
		for(int z=0;z<rows;z++){
			if(z!=i)
				if(arr[z][j]<=arr[i][j])
					return 0;
		}
		return 1;
	}
	else if(flag2==1){
		for(int z=0;z<rows;z++){
			if(z!=i)
				if(arr[z][j]>=arr[i][j])
					return 0;
		}
		return 1;
	}
}

void saddle_points(int **arr, int rows, int cols){
	int flag=0;
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			if(check(arr,rows,cols,i,j)==1){
				flag=1;
				printf("A[%d][%d] = %d\n",i,j,arr[i][j]);
			}
	if(flag==0)
		printf("No saddle points.\n");
}

int main(){
	int m,n;
	printf("Enter rows, columns: ");
	scanf("%d %d",&m,&n);
	int **A=create_2d_array(m,n);

	printf("Enter A[%d][%d] (one row at a time):\n",m,n);
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&A[i][j]);

	printf("Saddle points:\n");
	saddle_points(A,m,n);

	return 0;
}
