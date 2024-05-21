#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readFile(char filename[], char str[]){
	FILE *fptr=fopen(filename,"r");
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		exit(-1);
	}
	else
		printf("Input file successfully loaded.\n");

	int char_count=0;
	
	while(!feof(fptr)){
		str[char_count++]=fgetc(fptr);
	}
	fclose(fptr);
	return char_count;
}

void writeFile(char filename[], char str[], int count){
	FILE *fptr=fopen(filename,"w");
	if(fptr==NULL)
		printf("Error in output file creation.\n");
	else
		printf("Output file successfully created.\n");

	for(int i=count-1;i>=0;i--)
		fprintf(fptr,"%c",str[i]);

	fclose(fptr);
}

int main(int argc, char *argv[]){

	char infilename[100],outfilemame[100],string[100];
	int characters;

	if(argc!=3){
		printf ("Usage: ./a.out <in_file> <out_file>\n");
		exit(0);
	}
	else{
		strcpy(infilename, argv[1]);
		strcpy(outfilemame, argv[2]);
	}

	characters=readFile(infilename,string);
	writeFile(outfilemame,string,characters);
	
	return 0; 
}