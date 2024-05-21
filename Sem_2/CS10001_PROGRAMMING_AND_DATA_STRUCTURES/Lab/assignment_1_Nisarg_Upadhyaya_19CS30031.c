/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Palindrome or not*/

#include <stdio.h>

int main(){

	char str[100],temp;
	int len;

	printf("Enter a string (of at most 100 characters): ");
	scanf("%c",&temp);

	for(len=0;temp!='\n';len++){
		str[len]=temp;
		scanf("%c",&temp);
	}

	printf("Length of \"%s\" = %d\n",str,len);

	int lower=0,upper=len-1,flag=1;

	while(upper>=lower){
		if(str[lower]!=str[upper]){
			flag=0;
			break;
		}
		else{
			lower++;
			upper--;
		}
	}

	if(flag==0)
		printf("Not a palindrome.\n");
	else
		printf("Palindrome\n");

	return 0;
}
