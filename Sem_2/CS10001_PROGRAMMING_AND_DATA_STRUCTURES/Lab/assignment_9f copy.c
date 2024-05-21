#include <stdio.h>

int occ(int **arr1, int arr2[][2],int row, int col){
	int count=0;
	for(int i=0;i<row-1;i++)
		for(int j=0;j<col-1;j++)
			if((arr1[i][j]==arr2[0][0])&&(arr1[i][j+1]==arr2[0][1])&&(arr1[i+1][j]==arr2[1][0])&&(arr1[i+1][j+1]==arr2[1][1]))
				count++;
	return count;
}

int main(){
	int m,n;
	printf("Enter m, n: ");
	scanf("%d %d",&m,&n);

	int **A,B[2][2];
	A=(int **)malloc(m*sizeof(int *));
	for(int i=0;i<m;i++)
		A[i]=(int *)malloc(n*sizeof(int));

	printf("Enter A[%d][%d] (one row at a time):\n",m,n);
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&A[i][j]);
	printf("Enter B[2][2] (one row at a time):\n");
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			scanf("%d",&B[i][j]);

	printf("Number of occurences = %d",occ(A,B,m,n));

	return 0;
}
