/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 13(b)*/

#include <stdio.h>
#include <stdlib.h>

int string_match(char *str1, char *str2, int n, int m, int *diff){
	int min_diff=9999,curr_diff,index;
	for(int i=0;i<n-m+1;i++){
		curr_diff=0;
		for(int j=0;j<m;j++){
			if(str1[i+j]!=str2[j])
				curr_diff++;
		}
		if(curr_diff<min_diff){
			min_diff=curr_diff;
			index=i;
		}
		if(min_diff==0)
			break;
	}
	*diff=min_diff;
	return index;
}

int main(){
	int m,n;
	
	do{
		printf("Input m and n (m<n): ");
		scanf("%d %d",&m,&n);
	}while(m>=n);
	getchar();

	char *S=(char *)malloc(m*sizeof(char));
	char *T=(char *)malloc(n*sizeof(char));
	
	printf("Enter first string S (length %d): ",m);
	scanf("%[^\n]",S);
	getchar();
	printf("Enter second string T (length %d): ",n);
	scanf("%[^\n]",T);
	getchar();

	int difference;
	int best_index=string_match(T,S,n,m,&difference);

	if(difference==0)
		printf("Result = Yes\n");
	else{
		printf("Result = No\n");
		printf("Best match = ");
		for(int i=0;i<m;i++)
			printf("%c",T[best_index+i]);
		printf("\n");
		printf("Difference = %d\n",difference);
	}

	return 0;
}
