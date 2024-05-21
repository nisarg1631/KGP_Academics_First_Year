/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*String matching*/

#include <stdio.h>
#include <string.h>

int stringMatch(char s[], char t[]){
	int flag=1;
	for(int i=0;i<strlen(t);i++){
		if(s[i]!=t[i]){
			flag=0;
			return flag;
		}
	}
	return flag;
}

int main(){

	char str1[100],str2[100];

	printf("Enter first string (of at most 100 characters):");
	scanf("%[^\n]",str1);
	fflush(stdin);
	printf("Enter second string (of at most 100 characters):");
	scanf("%[^\n]",str2);

	if(strlen(str2)>strlen(str1)){
		char temp[100];
		strcpy(temp,str2);
		strcpy(str2,str1);
		strcpy(str1,temp);
	}

	int count=0;
	for(int i=0;i<strlen(str1)-strlen(str2)+1;i++){
		if(stringMatch(str1+i,str2)==1)
			count++;
	}

	printf("No. of matches = %d\n",count);

	return 0;
}
