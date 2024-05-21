/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 13(d)*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _LIFO{
	char data;
	struct _LIFO *next;
}stack;

stack *stackPush(stack *top, char input){
	stack *new=(stack *)malloc(sizeof(stack));
	if(new==NULL){
		printf("Stack overflow.\n");
		exit(-1);
	}
	else{
		new->data=input;
		new->next=top;
		return new;
	}
}

char stackPop(stack **top){
	if(*top==NULL){
		return 'u';
	}
	else{
		stack *temp;
		char value;
		temp=(*top);
		value=(*top)->data;
		*top=(*top)->next;
		free(temp);
		return value;
	}
}

int main(){
	stack *stack_top=NULL;
	char input,temp;
	int flag=1;

	printf("Enter a string: ");
	
	do{
		scanf("%c",&input);
		if(input=='(')
			stack_top=stackPush(stack_top,input);
		else if(input==')'){
			temp=stackPop(&stack_top);
			if(temp=='u'){
				printf("Unbalanced.\n");
				flag=0;
				break;
			}
		}
	}while(input!='$');

	if(flag==1){
		if(stackPop(&stack_top)=='u')
			printf("Balanced.\n");
		else
			printf("Unbalanced.\n");
	}
	
	return 0;
}