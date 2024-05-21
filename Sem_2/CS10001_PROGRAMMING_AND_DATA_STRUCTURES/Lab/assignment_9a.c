/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Pointer in C (9a)*/

#include <stdio.h>

int main(){
	int x;
	int *px=&x;
	printf("Enter an integer: ");
	scanf("%d",px);

	for(int i=0;i<2;i++){
		printf("Address of x = %u, x = %d\n",&x,x);
		printf("Address of px = %u, px = %u\n",&px,px);
		printf("Value stored in the address pointed by px = %d\n",*px);
		x*=2;
	}

	return 0;
}
