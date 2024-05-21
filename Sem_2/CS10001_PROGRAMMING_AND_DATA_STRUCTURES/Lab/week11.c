#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(char filename[], int *char_count, int *word_count, char words[][100]){
	FILE *fptr=fopen(filename,"r");
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		exit(-1);
	}
	else
		printf("Input file successfully loaded.\n");
	
	*char_count=0;
	*word_count=0;
	char temp;
	int i=0,flag=0;

	while(!feof(fptr)){
		temp=fgetc(fptr);
		(*char_count)++;
		if((temp>='A'&&temp<='Z')||(temp>='a'&&temp<='z')){
			if(flag==0){
				if(*word_count!=0)
					words[(*word_count)-1][i]='\0';
				(*word_count)++;
				i=0;
				flag=1;
			}
			words[(*word_count)-1][i++]=temp;
		}
		else{
			flag=0;
		}
	}
	if(words[(*word_count)-1][i]!='\0'){
		words[(*word_count)-1][i]='\0';
	}
	fclose(fptr);
}

void swap(char s1[], char s2[]){
	char temp[100];
	strcpy(temp,s1);
	strcpy(s1,s2);
	strcpy(s2,temp);
}

void sortWords(char words[][100],int word_count){
	int flag;
	for(int i=0;i<word_count;i++){
		flag=0;
		for(int j=0;j<word_count-i-1;j++){
			if(strcmp(words[j],words[j+1])>0){
				swap(words[j],words[j+1]);
				flag=1;
			}
		}
		if(flag==0)
			break;
	}
}

void writeFile(char filename[], char words[][100], int word_count){
	FILE *fptr=fopen(filename,"w");
	if(fptr==NULL)
		printf("Error in output file creation.\n");
	else
		printf("Output file successfully created.\n");

	for(int i=0;i<word_count;i++)
		fprintf(fptr,"%s\n",words[i]);

	fclose(fptr);
}

int main(int argc, char *argv[]){

	char infilename[100],outfilemame[100],words[1000][100],dist_words[1000][100];
	int char_count,word_count,dist_word_count,flag[1000]={0};

	if(argc!=3){
		printf ("Usage: ./a.out <in_file> <out_file>\n");
		exit(0);
	}
	else{
		strcpy(infilename, argv[1]);
		strcpy(outfilemame, argv[2]);
	}

	readFile(infilename,&char_count,&word_count,words);

	dist_word_count=0;
	for(int i=0;i<word_count;i++){
		if(flag[i]==1)
			continue;
		strcpy(dist_words[dist_word_count++],words[i]);
		for(int j=i+1;j<word_count;j++){
			if(strcmp(words[i],words[j])==0)
				flag[j]=1;
		}
	}
	
	sortWords(dist_words,dist_word_count);
	writeFile(outfilemame,dist_words,dist_word_count);
	
	printf("Total characters: %d, Total words: %d\n",char_count,word_count);
	
	return 0; 
}