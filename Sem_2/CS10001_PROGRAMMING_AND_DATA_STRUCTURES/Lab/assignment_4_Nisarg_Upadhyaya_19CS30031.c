/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Convert to upper case*/

void toUpper(char str[]){
	for(int i=0;str[i]!='\0';i++){
		if(str[i]>='a'&&str[i]<='z')
			str[i]=str[i]+'A'-'a';
	}
}

#include <stdio.h>

int main(){

		char str[100][25];
		int n;

		printf("Enter the value of n (at most 100): ");
		scanf("%d",&n);

		printf("Enter %d strings (of length at most 20): ",n);

		for(int i=0;i<n;i++){
			scanf("%s",str[i]);
		}

		printf("Result: ");

		for(int i=0;i<n;i++){
			toUpper(str[i]);
			printf("%s ",str[i]);
		}
		printf("\n");
		
	return 0;
}
