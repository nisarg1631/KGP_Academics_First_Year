/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Sorting with pointers (9b)*/

#include <stdio.h>

void swap(int *n1, int *n2){
	int temp;
	temp=*n1;
	*n1=*n2;
	*n2=temp;
}

void sort(int *a,int *b, int *c){
	if(*a>*b)
		swap(a,b);
	if(*b>*c)
		swap(b,c);
	if(*a>*b)
		swap(a,b);
}

int main(){
	int a,b,c;
	printf("Enter three integers: ");
	scanf("%d %d %d",&a,&b,&c);

	printf("---Before function call---\n");
	printf("Address of a = %u\n",&a);
	printf("Address of b = %u\n",&b);
	printf("Address of c = %u\n",&c);
	printf("Values in a, b, c = %d, %d, %d\n",a,b,c);

	sort(&a,&b,&c);

	printf("---After function call---\n");
	printf("Address of a = %u\n",&a);
	printf("Address of b = %u\n",&b);
	printf("Address of c = %u\n",&c);
	printf("Values in a, b, c = %d, %d, %d\n",a,b,c);

	return 0;
}
