/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 13(a)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int m,n;
	
	printf("Enter length of first string (m): ");
	scanf("%d",&m);
	printf("Enter length of second string (n): ");
	scanf("%d",&n);
	getchar();
	
	char *S=(char *)malloc(m*sizeof(char));
	char *T=(char *)malloc(n*sizeof(char));
	char *result=(char *)malloc((m+n)*sizeof(char));
	
	printf("Enter first string S (length %d): ",m);
	scanf("%[^\n]",S);
	getchar();
	printf("Enter second string T (length %d): ",n);
	scanf("%[^\n]",T);
	getchar();

	printf("S = %s\n",S);
	printf("T = %s\n",T);

	strcpy(result,S);
	strcat(result,T);
	printf("Result of S+T = %s\n",result);
	
	strcpy(result,T);
	strcat(result,S);
	printf("Result of T+S = %s\n",result);

	return 0;
}
