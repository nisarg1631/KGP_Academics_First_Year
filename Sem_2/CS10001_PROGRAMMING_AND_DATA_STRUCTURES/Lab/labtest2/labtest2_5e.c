/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Lab Test 2 - 5e*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
	int x,f;
	struct _NODE *next;
}node;

void printList(node **head){
	node *it=*head;
	printf("L =");
	while(it!=NULL){
		if(it->next==NULL)
			printf(" %d-%d.\n",it->x,it->f);
		else
			printf(" %d-%d,",it->x,it->f);
		it=it->next;
	}
}

void insertNumber(node **head, int num){
	node *new_node=(node *)malloc(sizeof(node));
	new_node->x=num;
	
	node *it=*head,*prev;

	if(it==NULL){
		new_node->f=1;
		new_node->next=NULL;
		*head=new_node;
		return;
	}
	while(it!=NULL){
		if(it->x>num){
			new_node->f=1;
			new_node->next=it;
			if(it==*head){
				*head=new_node;
				return;
			}
			else{
				prev->next=new_node;
				return;
			}
		}
		if(it->x==num){
			(it->f)++;
			free(new_node);
			return;
		}
		prev=it;
		it=it->next;
	}
	//if function reaches this part it means num is greater than all values stored, insert it at end
	new_node->f=1;
	new_node->next=NULL;
	prev->next=new_node;
}

int main(){
	node *head=NULL;
	int num;

	printf("Enter data (enter 0 to terminate input):\n");
	while(1){
		scanf("%d",&num);
		if(num<=0)
			break;
		insertNumber(&head,num);
	}
	printList(&head);

	return 0;
}