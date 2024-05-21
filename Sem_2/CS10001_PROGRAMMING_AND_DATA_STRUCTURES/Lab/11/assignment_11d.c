/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 11(d)*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char name[30],surname[30];
	int roll_no;
	float p,c,m;
}_STU;

#define MAXSIZE 1000

_STU student[MAXSIZE];
int count=0;

int bin_search(int x){
	int lo=0,hi=count-1,mid;
	while(hi>=lo){
		mid=(hi+lo)/2;
		if(student[mid].roll_no==x){
			return mid;
		}
		else{
			if(x<student[mid].roll_no){
				hi=mid-1;
			}
			else{
				lo=mid+1;
			}
		}
	}
	return -1;
}

void view_rec(){
	printf("-----------------------------------------------\n");
	for(int i=0;i<count;i++)
		printf("%d %s %s %.2f %.2f %.2f\n",student[i].roll_no,student[i].name,student[i].surname,student[i].p,student[i].c,student[i].m);
	printf("-----------------------------------------------\n");
}

void countStudents(){
	FILE *fptr=fopen("student.txt","r");
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		exit(-1);
	}
	else
		printf("Input file successfully loaded.\n");
	
	char temp;
	while(!feof(fptr)){
		temp=fgetc(fptr);
		if(temp=='\n')
			count++;
	}
	count++;
	fclose(fptr);
}

void readFile(){
	FILE *fptr=fopen("student.txt","r");
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		exit(-1);
	}

	countStudents();
	
	for(int i=0;i<count;i++)
		fscanf(fptr,"%d %s %s %f %f %f",&student[i].roll_no,student[i].name,student[i].surname,&student[i].p,&student[i].c,&student[i].m);

	fclose(fptr);
}

void merge(int size1, int size2, _STU *A, _STU *B, _STU *C){
	int i=0,j=0,k=0;
	while(i<size1&&j<size2){
		if(A[i].roll_no>=B[j].roll_no){
			C[k]=B[j];
			k++;
			j++;
		}
		else{
			C[k]=A[i];
			k++;
			i++;
		}
	}	
	if(i==size1){
		for(int z=j;z<size2;z++){
			C[k]=B[z];
			k++;
		}
	}
	else{
		for(int z=i;z<size1;z++){
			C[k]=A[z];
			k++;
		}
	}
}

void merge_sort(_STU *arr, int size){
	if(size>1){
		int size1,size2;
		size1=size/2;
		size2=size-size1;
		
		_STU *arr1=(_STU *)malloc(size1*sizeof(_STU));
		_STU *arr2=(_STU *)malloc(size2*sizeof(_STU));

		for(int i=0;i<size;i++){
			if(i<size1)
				arr1[i]=arr[i];
			else
				arr2[i-size1]=arr[i];
		}
		
		merge_sort(arr1,size1);
		merge_sort(arr2,size2);
		merge(size1,size2,arr1,arr2,arr);

		free(arr1);
		free(arr2);
	}
}

void writeFile(){
	FILE *fptr=fopen("student.txt","w");
	if(fptr==NULL){
		printf("Error in output file creation.\n");
		exit(-1);
	}
	
	for(int i=0;i<count;i++){
		if(i==count-1)	//last entry then dont add new line at end
			fprintf(fptr,"%d %s %s %.2f %.2f %.2f",student[i].roll_no,student[i].name,student[i].surname,student[i].p,student[i].c,student[i].m);
		else
			fprintf(fptr,"%d %s %s %.2f %.2f %.2f\n",student[i].roll_no,student[i].name,student[i].surname,student[i].p,student[i].c,student[i].m);			
	}
	fclose(fptr);
}

void add_rec(int r_num){
	if(bin_search(r_num)!=-1)
		printf("Roll number already exists.\n");
	else{
		printf("Name: ");
		scanf("%s", student[count].name);
		printf("Surame: ");
		scanf("%s", student[count].surname);
		printf("Marks in Physics: ");
		scanf("%f",&student[count].p);
		printf("Marks in Chemistry: ");
		scanf("%f",&student[count].c);
		printf("Marks in Maths: ");
		scanf("%f",&student[count].m);
		student[count].roll_no=r_num;
		count++;
		merge_sort(student,count);
		writeFile();
		printf("Record added.\n");
	}
}

void del_rec(int r_num){
	int flag=bin_search(r_num);
	if(flag==-1){
		printf("Roll number does not exist.\n");
	}
	else{
		for(int i=flag;i<count-1;i++){
			student[i]=student[i+1];
		}
		count--;
		writeFile();
		printf("Record deleted.\n");
	}
}

int main(){
	readFile();
	merge_sort(student,count);
	
	int opt;

	while(1){
		printf("Choose operation from given list:\n");
		printf("1> Add student record\n");
		printf("2> Delete student record (by roll number)\n");
		printf("3> Search student record (by roll number)\n");
		printf("4> View all student records\n");
		printf("5> Exit\n");

		scanf("%d",&opt);

		if(opt==1){
			int temp;
			printf("Enter roll number to add: ");
			scanf("%d",&temp);
			getchar();
			add_rec(temp);
		}

		else if(opt==2){
			int temp;
			printf("Enter roll number to delete: ");
			scanf("%d",&temp);
			del_rec(temp);
		}

		else if(opt==3){
			int temp;
			printf("Enter roll number to search: ");
			scanf("%d",&temp);
			int search=bin_search(temp);
			if(search==-1)
				printf("No record found for given roll number.\n");
			else{
				printf("Name: %s %s\n",student[search].name,student[search].surname);
				printf("Physics marks: %.2f\n",student[search].p);
				printf("Chemistry marks: %.2f\n",student[search].c);
				printf("Maths marks: %.2f\n",student[search].m);
			}
		}

		else if(opt==4){
			view_rec();
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