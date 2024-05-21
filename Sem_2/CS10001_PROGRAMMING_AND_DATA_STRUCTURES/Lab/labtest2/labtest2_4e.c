/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Lab Test 2 - 4e*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float **create_2d_array(int rows, int cols){
	float **arr;
	arr=(float **)malloc(rows*sizeof(float *));
	for(int i=0;i<rows;i++)
		arr[i]=(float *)malloc(cols*sizeof(float));
	return arr;
}

float **readFile(int *p, int *b){
	FILE *fptr=fopen("t4e.txt","r");
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		exit(-1);
	}
	else
		printf("Input file successfully loaded.\n");
	
	fscanf(fptr,"%d %d",p,b);
	float **data=create_2d_array(*p,*b);
	
	for(int i=0;i<(*p);i++)
		for(int j=0;j<(*b);j++)
			fscanf(fptr,"%f",&data[i][j]);

	fclose(fptr);
	return data;
}

void getTopBids(float **arr, int *top, int p, int b){
	float max;
	for(int j=0;j<b;j++){
		max=-1.0;
		for(int i=0;i<p;i++){
			if(arr[i][j]>max){
				max=arr[i][j];
				top[j]=i+1;
			}
		}
	}
}

int maxHighBid(int *top, int b, int p, int *best){
	int *freq=(int *)malloc((p+1)*sizeof(int));
	int max_index, max_freq=0;
	for(int i=0;i<b;i++){
		freq[top[i]]++;
		if(freq[top[i]]>max_freq){
			max_freq=freq[top[i]];
			max_index=top[i];
		}
	}
	*best=max_index;
	return freq[max_index]; 
}

void getBestBidders(int *best, int *best_count, int *top, int b, int p){
	int limit=(int)ceil((3*b)/4.0), highbid; //taking ceiling of 3/4 th bidders, nothing was mentioned in question
	if(maxHighBid(top,b,p,&highbid)>=limit){
		printf("Best painting: %d.\n",highbid);
		for(int i=0; i<b; i++){
			if(top[i]==highbid){
				best[(*best_count)++]=i+1;
			}
		}
	}
	else{
		*best_count=0;
	}
}

int main(){
	int p,b;
	float **auction=readFile(&p,&b);
	
	for(int i=0;i<p;i++){
		for(int j=0;j<b;j++){
			printf("%.1f ",auction[i][j]);
		}
		printf("\n");
	}
	printf("#paintings = %d\n",p);
	printf("#bidders = %d\n",b);
	
	int *top_bids=(int *)malloc(b*sizeof(int));
	getTopBids(auction,top_bids,p,b);

	printf("Top bids by the %d bidders:",b);
	for(int i=0;i<b;i++){
		if(i==(b-1))
			printf(" %d.\n",top_bids[i]);
		else
			printf(" %d,",top_bids[i]);
	}

	int *best=(int *)malloc(b*sizeof(int)),best_count;
	getBestBidders(best,&best_count,top_bids,b,p);

	if(best_count==0){
		printf("No best painting.\n");
	}
	else{
		printf("Bidders with the best painting as their top bid: ");
		for(int i=0;i<best_count;i++){
			if(i==(best_count-1))
				printf(" %d.\n",best[i]);
			else
				printf(" %d,",best[i]);
		}
	}
	
	return 0;
}