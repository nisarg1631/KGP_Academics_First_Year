/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Lab Test 2 - 2e*/

#include <stdio.h>

#define DIGITS 6
#define MAX_PERM 64

int checkPermutation(int arr[], int c, int d){
	int limit=((4*c)+d+5), sum=0;
	for(int i=0;i<DIGITS;i++)
		sum+=arr[i];

	if(sum<=limit)
		return 1;
	else
		return 0;
}

void generatePermutation(int arr[], int c, int d, int index, int answer[][DIGITS], int *answer_count){
	if(index==DIGITS){
		if(checkPermutation(arr,c,d)){
			for(int i=0;i<DIGITS;i++)
				answer[*answer_count][i]=arr[i];
			(*answer_count)++;
		}
		return;
	}

	arr[index]=c;
	generatePermutation(arr,c,d,index+1,answer,answer_count);

	arr[index]=d;
	generatePermutation(arr,c,d,index+1,answer,answer_count);
}

int main(){
	int c,d;
	
	do{
		printf("Enter two distinct digits from 1 to 9: ");
		scanf("%d %d",&c,&d);
		if((c==d)||c<1||c>9||d<1||d>9)
			printf("Enter a valid input.\n");
	}while((c==d)||c<1||c>9||d<1||d>9);

	int answer[MAX_PERM][DIGITS], count=0, array[DIGITS];
	generatePermutation(array,c,d,0,answer,&count);

	printf("Count: %d\n",count);
	printf("Numbers:\n");
	for(int i=0;i<count;i++){
		for(int j=0;j<DIGITS;j++){
			printf("%d",answer[i][j]);
		}
		printf("\n");
	}

	return 0;
}
