/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 11(c)*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char name[30],surname[30];
	int roll_no;
	float p,c,m;
}_STU;

int countStudents(){
	FILE *fptr=fopen("student.txt","r");
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		exit(-1);
	}
	else
		printf("Input file successfully loaded.\n");
	
	int count=0;
	char temp;
	while(!feof(fptr)){
		temp=fgetc(fptr);
		if(temp=='\n')
			count++;
	}
	count++;
	fclose(fptr);
	return count;
}

_STU * readFile(int *count){
	FILE *fptr=fopen("student.txt","r");
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		exit(-1);
	}
	else
		printf("Input file successfully loaded.\n");
	
	*count=countStudents();
	_STU *student=(_STU *)malloc((*count)*(sizeof(_STU)));
	
	for(int i=0;i<*count;i++)
		fscanf(fptr,"%d %s %s %f %f %f",&student[i].roll_no,student[i].name,student[i].surname,&student[i].p,&student[i].c,&student[i].m);

	fclose(fptr);
	return student;
}

void merge(int size1, int size2, _STU *A, _STU *B, _STU *C){
	int i=0,j=0,k=0;
	while(i<size1&&j<size2){
		if((A[i].p+A[i].c+A[i].m)<=(B[j].p+B[j].c+B[j].m)){
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

char * getGrades(_STU *student, int count){
	char *grades=(char *)malloc(count*sizeof(char));
	float avg;
	for(int i=0;i<count;i++){
		avg=(student[i].p+student[i].c+student[i].m)/3;
		if(avg>90.0)
			grades[i]='A';
		else if(avg>80.0)
			grades[i]='B';
		else if(avg>70.0)
			grades[i]='C';
		else if(avg>60.0)
			grades[i]='D';
		else if(avg>50.0)
			grades[i]='E';
		else if(avg>30.0)
			grades[i]='P';
		else
			grades[i]='F';
	}
	return grades;
}

void writeFile(_STU *student, int count){
	FILE *fptr=fopen("grade.txt","w");
	if(fptr==NULL){
		printf("Error in output file creation.\n");
		exit(-1);
	}
	else
		printf("Output file successfully created.\n");

	char *grade_list=getGrades(student,count);
	
	for(int i=0;i<count;i++)
		fprintf(fptr,"%s %s, %d, %.2f, %c\n",student[i].name,student[i].surname,student[i].roll_no,student[i].p+student[i].c+student[i].m,grade_list[i]);

	fclose(fptr);
}

int main(){
	int count;
	_STU *class=readFile(&count);

	merge_sort(class,count);
	writeFile(class,count);
	
	return 0;
}