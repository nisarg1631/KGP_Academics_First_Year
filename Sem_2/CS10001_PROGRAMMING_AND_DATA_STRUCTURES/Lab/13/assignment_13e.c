/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 13(e)*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int p,t;
}job;

typedef struct _FIFO{
	job data;
	struct _FIFO *next;
}queue;

void print_queue(queue *front){
	queue *it=front;
	while(it!=NULL){
		printf("(%d,%d) ",it->data.p,it->data.t);
		it=it->next;
	}
	printf("\n");
}

void enqueue(queue **front, queue **rear, job input){
	queue *new=(queue *)malloc(sizeof(queue));
	if(new==NULL){
		printf("Queue overflow.\n");
	}
	else{
		new->data=input;
		new->next=NULL;
		if(*front==NULL)
			*front=*rear=new;
		else{
			(*rear)->next=new;
			*rear=new;
		}
	}
}

job dequeue(queue **front, queue **rear){
	job value;
	if(*front==NULL){
		value.p=-1;
		value.t=-1;
	}
	else{
		queue *temp;
		temp=(*front);
		value=(*front)->data;
		if(*front==*rear)
			*rear=NULL;
		*front=(*front)->next;
		free(temp);
	}	
	return value;
}

int main(){
	queue *front,*rear;
	front=rear=NULL;
	int size=0;
	job input;

	printf("Enter as many jobs as you want. To terminate input enter p to be any integer not equal to 1,2, or 3.\n");
	do{
		printf("Enter p and t: ");
		scanf("%d %d",&input.p,&input.t);
		if(input.p==1||input.p==2||input.p==3){
			enqueue(&front,&rear,input);
			size++;
		}
		printf("Jobs: ");
		print_queue(front);
	}while(input.p==1||input.p==2||input.p==3);
	
	printf("Printed: ");
	int current_size,current_search=3;
	while(size!=0){
		current_size=size;
		for(int i=0;i<current_size;i++){
			input=dequeue(&front,&rear);
			if(input.p==current_search){
				printf("(%d,%d) ",input.p,input.t);
				size--;
			}
			else
				enqueue(&front,&rear,input);
		}
		current_search--;
	}
	printf("\n");

	return 0;
}