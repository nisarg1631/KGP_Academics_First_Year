/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*String formating*/

#include <stdio.h>
#include <string.h>

void toLower(char str[]){
	for(int i=0;str[i]!='\0';i++){
		if(str[i]>='A'&&str[i]<='Z')
			str[i]=str[i]+'a'-'A';
	}
}

int main(){

	char str[25],new[25];

	printf("Enter X (of at most 20 characters):");
	scanf("%[^\n]",str);

	int len=0,i=0;

	while(len<strlen(str)){
		if(str[len]==' '&&(len==0||len==strlen(str)-1||str[len-1]==' ')){
			len++;
		}
		else{
			new[i]=str[len];
			len++;
			i++;
		}
	}

	if(new[i-1]==' '){
		if(new[i-2]=='.')
			new[i-1]='\0';
		else{
			new[i-1]='.';
			new[i]='\0';
		}
	}
	else{
		if(new[i-1]=='.')
			new[i]='\0';
		else{
			new[i]='.';
			new[i+1]='\0';
		}
	}

	toLower(new);
	new[0]=new[0]+'A'-'a';

	printf("Answer:%s\n",new);

	return 0;
}
