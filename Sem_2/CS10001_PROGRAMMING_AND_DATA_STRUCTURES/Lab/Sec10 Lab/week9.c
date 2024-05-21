#include <stdio.h>
#include <string.h>

#define MAXC 15
#define MAXW 100

typedef struct{
	char word[MAXC],sorted[MAXC];
}word_t;

int readwords(word_t wordlist[]){
	int n;
	printf("Enter number of words: ");
	scanf("%d",&n);
	printf("Enter %d words: ",n);
	for(int i=0;i<n;i++)
		scanf("%s",wordlist[i].word);
	return n;
}

void sortword(word_t* pword){
	strcpy(pword->sorted,pword->word);
	int flag;
	char temp;

	for(int i=0;i<strlen(pword->sorted)-1;i++){
		flag=0;
		for(int j=0;j<strlen(pword->sorted)-i-1;j++){
			if(pword->sorted[j]>pword->sorted[j+1]){
				temp=pword->sorted[j];
				pword->sorted[j]=pword->sorted[j+1];
				pword->sorted[j+1]=temp;
				flag=1;
			}
		}
		if(flag==0)
			return;
	}
}

int is_anagram(word_t* pword1, word_t* pword2){
	if(strcmp(pword1->sorted,pword2->sorted)==0)
		return 1;
	else
		return 0;
}

void sortwordlist(word_t wordlist[],int wordcount){
	int flag;
	word_t temp;

	for(int i=0;i<wordcount-1;i++){
		flag=0;
		for(int j=0;j<wordcount-i-1;j++){
			if(strcmp(wordlist[j].sorted,wordlist[j+1].sorted)>0){
				temp=wordlist[j];
				wordlist[j]=wordlist[j+1];
				wordlist[j+1]=temp;
				flag=1;
			}
		}
		if(flag==0)
			return;
	}
}

void printanagrams(word_t wordlist[],int wordcount){
	sortwordlist(wordlist,wordcount);
	printf("\n%s",wordlist[0].word);
	for(int i=1;i<wordcount;i++){
		if(is_anagram(&wordlist[i-1],&wordlist[i])==1)
			printf(" %s",wordlist[i].word);
		else
			printf("\n%s",wordlist[i].word);
	}
}

int main(){
	word_t wordlist[MAXW];

	int n=readwords(wordlist);
	for(int i=0;i<n;i++)
		sortword(&wordlist[i]);
	printf("Anagrams:");
	printanagrams(wordlist,n);

	return 0;
}
