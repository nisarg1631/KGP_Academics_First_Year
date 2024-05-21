/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Lab Test 2 - 1e*/

#include <stdio.h>

int main(){
	int n;
	
	printf("Enter n: ");
	scanf("%d",&n);
	
	printf("Answer: ");
	if(n%6==0){
		printf("%d+%d+%d\n",(n/3)-2,(n/3),(n/3)+2);
	}
	else{
		printf("No.\n");
	}

	return 0;
}
