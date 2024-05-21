/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 12(d) - Bubble sort on linked list*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
	int data;
	struct _NODE *next;
}node;

node *swap(node* n1, node* n2) { 
    node *temp=n2->next; 
    n2->next=n1; 
    n1->next=temp; 
    return n2; 
}

void display(node *head){
	node *it=head;
	printf("List contains: ");
	if(head==NULL)
		printf("Empty");
	while(it!=NULL){
		if(it->next==NULL)
			printf("%d",it->data);
		else
			printf("%d -> ",it->data);
		it=it->next;
	}
	printf("\n");
}

void insert(node **head, int input){
	node *new=(node *)malloc(sizeof(node));
	new->data=input;
	new->next=*head;
	*head=new;
}

void bubble_sort(node **head){
	node *it1,**it2,*n;
	it1=NULL;
	int flag;
	do{
		flag=0;
		it2=head;
		while(((*it2)->next)!=it1){
			n=*it2;
			if((n->data)>(n->next->data)){
				*it2=swap(n,n->next);
				flag=1;
			}
			it2=&((*it2)->next);
		}
		it1=*it2;
	}while(flag);
}

int main(){
	node *head=NULL;
	int x;

	printf("Enter positive integers to add to list. Enter 0 to terminate input.\n");
	do{
		printf("Enter element: ");
		scanf("%d",&x);
		if(x>0)
			insert(&head,x);
		else if(x<0)
			printf("Enter positive integers only.\n");
		display(head);
	}while(x!=0);
	printf("Input terminated.\n");

	bubble_sort(&head);
	printf("--- BUBBLE SORT ----\n");
	display(head);

	return 0;
}
