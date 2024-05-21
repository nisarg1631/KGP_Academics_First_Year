#include <stdio.h>
#include <stdlib.h>

//student record structure
typedef struct _STUDENT{
	char name[50],roll_no[20];
	float cgpa;
}student;

//structure for a node of a stack
typedef struct _LIFO{
	student data;
	struct _LIFO *next;
}stack;

//structure for a queue using two stacks, the primary stack is our queue where the stack top is the queue front and stack bottom is the queue end, the secondary stack is used for the enqueue operation
typedef struct _FIFO{
	stack **primary, **secondary;
	int size;
}queue;

//allocates memory for storing pointer to a stack node which always points to the top of stack, initialises it to NULL and returns the address of the memory location
stack **initialiseStack(){
	stack **ptr=(stack **)malloc(sizeof(stack *));
	*ptr=NULL;
	return ptr;
}

//pushes an element to a stack by allocating memory and modifies the top of stack, new top points to the previous top, if memory allocation fails then program exits
void push(stack **top, student input){
	stack *new=(stack *)malloc(sizeof(stack));
	if(new==NULL){
		printf("Stack overflow.\n");
		exit(-1);
	}
	else{
		new->data=input;
		new->next=*top;
		*top=new;
	}
}

//removes element from top of stack, frees the memory, and returns the element which is removed, if stack is empty it returns a student record with a negative CGPA
student pop(stack **top){
	student value;
	if(*top==NULL)
		value.cgpa=(float)-1;	//negative cgpa used to imply no data present
	else{
		stack *temp;
		temp=(*top);
		value=(*top)->data;
		*top=(*top)->next;
		free(temp);
	}
	return value;	
}

//checks if stack is empty or not by checking whether the top of the stack is a NULL pointer or not
int isEmptyStack(stack **top){
	if(*top==NULL)
		return 1;
	else
		return 0;
}

//initialises a queue by initialising the two stacks in it using the initialiseStack function and its size to 0
queue *initialiseQueue(){
	queue *ptr=(queue *)malloc(sizeof(queue));
	ptr->primary=initialiseStack();
	ptr->secondary=initialiseStack();
	ptr->size=0;
	return ptr;
}

//as the stack bottom of primary stack is our queue end where new elements are added, first we empty the whole stack into the secondary stack, push our element to it, and then fill it back
void addQueue(queue *ptr, student input){
	while(!isEmptyStack(ptr->primary)){
		push(ptr->secondary,pop(ptr->primary));
	}
	push(ptr->primary,input);
	while(!isEmptyStack(ptr->secondary)){
		push(ptr->primary,pop(ptr->secondary));
	}
}

//as the stack top of primary stack is our queue front from where elements are deleted, we simply pop the element from the stack
student deleteQueue(queue *ptr){
	return pop(ptr->primary);
}

//as the primary stack is our queue, we check using the isEmptyStack function whether primary stack is empty or not
int isEmptyQueue(queue *ptr){
	return isEmptyStack(ptr->primary);
}

//as we are required to use only queue functions to display the queue, we iterate once over the whole queue by repetitively deleting an element from it, printing the data in it and adding it back to the queue, this way the queue returns to its original state after a complete iteration
void displayQueue(queue *ptr){
	if(isEmptyQueue(ptr))
		printf("Queue is empty.\n\n");
	else{
		printf("----STUDENT RECORDS START----\n");
		for(int i=0;i<(ptr->size);i++){
			student temp=deleteQueue(ptr);
			printf("%d>\n",i+1);
			printf("Name: %s\n",temp.name);
			printf("Roll No: %s\n",temp.roll_no);
			printf("CGPA: %.2f\n",temp.cgpa);
			addQueue(ptr,temp);
		}
		printf("----STUDENT RECORDS END----\n\n");
	}	
}

//uses the same concept as in the displayQueue function, additionally keeping a track of the maximum cgpa encountered and storing the data of students with maximum cgpa in toppers array, a max_count paramater is passed to the function which is modified to store the number of students with maximum cgpa
student *findMaxQueue(queue *ptr, int *max_count){
	student *toppers=(student *)malloc((ptr->size)*sizeof(student));
	int count;
	float max_cgpa=(float)-1;
	for(int i=0;i<(ptr->size);i++){
		student temp=deleteQueue(ptr);
		if(temp.cgpa>max_cgpa){
			count=0;
			max_cgpa=temp.cgpa;
			toppers[count++]=temp;
		}
		else if(temp.cgpa==max_cgpa)
			toppers[count++]=temp;
		addQueue(ptr,temp);
	}
	*max_count=count;
	return toppers;
}

int main(){
	
	queue *records=initialiseQueue();
	int opt;

	while(1){
		printf("Choose operation from given list:\n");
		printf("1> Add a student's record\n");
		printf("2> Delete a student's record\n");
		printf("3> Display queue\n");
		printf("4> Print records of toppers\n");
		printf("5> Exit\n");
		printf(">>");

		scanf("%d",&opt);
		getchar();
		printf("\n");

		if(opt==1){
			student temp;
			printf("Enter student data to add:-\n");
			printf("Name: ");
			scanf("%[^\n]",&temp.name);
			getchar();
			printf("Roll No: ");
			scanf("%s",&temp.roll_no);
			getchar();
			printf("CGPA: ");
			scanf("%f",&temp.cgpa);
			getchar();
			addQueue(records,temp);
			(records->size)++;		//increase record size by 1
			printf("Record added to queue.\n\n");
		}

		else if(opt==2){
			student temp=deleteQueue(records);
			if(temp.cgpa==(float)-1)	//deleteQueue function returns student data with negative cgpa if queue is empty
				printf("Queue is empty.\n\n");
			else{
				printf("Record of following student removed:-\n");
				printf("Name: %s\n",temp.name);
				printf("Roll No: %s\n",temp.roll_no);
				printf("CGPA: %.2f\n\n",temp.cgpa);
				(records->size)--;		//decrease record size by 1
			}
		}

		else if(opt==3)
			displayQueue(records);

		else if(opt==4){
			if(isEmptyQueue(records))
				printf("Queue is empty.\n\n");
			else{
				int count;		//count is passed to function findMaxQueue to store number of students with maximum cgpa, used during iteration of toppers array
				student *toppers=findMaxQueue(records,&count);
				printf("----TOPPER RECORDS START----\n");
				for(int i=0;i<count;i++){
					printf("%d>\n",i+1);
					printf("Name: %s\n",toppers[i].name);
					printf("Roll No: %s\n",toppers[i].roll_no);
					printf("CGPA: %.2f\n",toppers[i].cgpa);
				}
				printf("----TOPPER RECORDS END----\n\n");
			}
		}

		else if(opt==5){
			printf("Bye\n");
			break;
		}

		else
			printf("Enter a valid option.\n");
	}
	return 0;
}