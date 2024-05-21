#include <stdio.h>
#include <stdlib.h>

void format_lines(char infilename[], char outfilename[]){
	FILE *fptr_in=fopen(infilename,"r");
	FILE *fptr_out=fopen(outfilename,"w");
	if(fptr_in==NULL||fptr_out==NULL){
		printf("Error in loading files.\n");
		exit(-1);
	}
	else
		printf("Files successfully loaded.\n");

	int flag=1;
	char temp;
	
	while(!feof(fptr_in)){
		temp=fgetc(fptr_in);
		if(temp=='.'){
			fputc(temp,fptr_out);
			flag=1;
		}
		else if(temp>='a'&&temp<='z'){
			if(flag==1){
				fputc(temp+'A'-'a',fptr_out);
				flag=0;
			}
			else{
				fputc(temp,fptr_out);
			}
		}
		else{
			if(temp>='A'&&temp<='Z'){
				if(flag==1){
					flag=0;
				}
			}
			fputc(temp,fptr_out);
		}
	}
}

int main(){

	char infilename[100],outfilename[100];
	
	printf("Enter input filename: ");
	scanf("%s",infilename);
	printf("Enter output filename: ");
	scanf("%s",outfilename);
	
	format_lines(infilename,outfilename);

	return 0; 
}