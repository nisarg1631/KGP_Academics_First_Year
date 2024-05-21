#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char roll_no[10],name[100],dob[20];
	float cgpa;
}_STUD_RECORD;

_STUD_RECORD * readStudentRecords(int *student_count){
	FILE *fptr=fopen("input.txt","r"); //write input1.txt for first set of inputs and input2.txt for second set
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		exit(-1);
	}
	else
		printf("Input file successfully loaded.\n");
	
	int count;
	char buffer;
	fscanf(fptr,"%d",&count);
	_STUD_RECORD *student=(_STUD_RECORD *)malloc(count*sizeof(_STUD_RECORD));
	*student_count=count;

	buffer=fgetc(fptr);
	for(int i=0;i<count;i++){
		buffer=fgetc(fptr);
		fscanf(fptr,"%[^\n]",&student[i].name);
		buffer=fgetc(fptr);
		fscanf(fptr,"%[^\n]",&student[i].roll_no);
		buffer=fgetc(fptr);
		fscanf(fptr,"%f",&student[i].cgpa);
		buffer=fgetc(fptr);
		fscanf(fptr,"%[^\n]",&student[i].dob);
		buffer=fgetc(fptr);
	}

	fclose(fptr);
	return student;
}

void swap(_STUD_RECORD *s1, _STUD_RECORD *s2){
	_STUD_RECORD temp;
	temp=*s1;
	*s1=*s2;
	*s2=temp;
}

void sortStudentRecords(_STUD_RECORD *student, _STUD_RECORD *s_arr, int s_count){
	for(int i=0;i<s_count;i++)
		s_arr[i]=student[i];

	int flag;
	for(int i=0;i<s_count;i++){
		flag=0;
		for(int j=0;j<s_count-i-1;j++){
			if(strcmp(s_arr[j].roll_no,s_arr[j+1].roll_no)>0){
				swap(&s_arr[j],&s_arr[j+1]);
				flag=1;
			}
		}
		if(flag==0)
			break;
	}
}

int * getStudentMaxCGPA(_STUD_RECORD *student, int s_count, int *max_count){
	float max=-1;
	int top, *max_arr=(int *)malloc(s_count*sizeof(int));
	for(int i=0;i<s_count;i++){
		if(student[i].cgpa>max){
			max=student[i].cgpa;
			top=0;
			max_arr[top]=i;
			top++;
		}
		else if(student[i].cgpa==max){
			max_arr[top]=i;
			top++;
		}
	}
	*max_count=top;
	return max_arr;
}

_STUD_RECORD getYoungestStudent(_STUD_RECORD *student, int s_count){
	_STUD_RECORD young;
	young=student[0];
	for(int i=1;i<s_count;i++){
		if(strncmp(young.dob+6,student[i].dob+6,4)<0){
			young=student[i];
			continue;
		}
		else if(strncmp(young.dob+3,student[i].dob+3,2)<0&&strncmp(young.dob+6,student[i].dob+6,4)==0){
			young=student[i];
			continue;
		}
		else if(strncmp(young.dob,student[i].dob,2)<0&&strncmp(young.dob+6,student[i].dob+6,4)==0&&strncmp(young.dob+3,student[i].dob+3,2)==0){
			young=student[i];
			continue;
		}
	}
	return young;
}

int getRecord(_STUD_RECORD *A, int n, char key[], int *pos){
	int lo=0,hi=n-1,mid,count=0;

	while(hi>=lo){
		
		mid=(hi+lo)/2;
		
		if(strncmp(A[mid].roll_no,key,8)==0){
			*pos=mid;
			count++;
			return count;
		}
		else{
			if(strncmp(A[mid].roll_no,key,8)>0){
				count++;
				hi=mid-1;
			}
			else{
				count++;
				lo=mid+1;
			}
		}
	}

	return -count;
}

int main(){

	int count, max_cgpa_count, *max_cgpa;
	_STUD_RECORD *student, *sorted, youngest;
	
	student=readStudentRecords(&count);
	sorted=(_STUD_RECORD *)malloc(count*sizeof(_STUD_RECORD));
	sortStudentRecords(student,sorted,count);

	FILE *fptr=fopen("output.txt","w");
	if(fptr==NULL){
		printf("Error in file creation.\n");
	}
	else
		printf("Output file successfully created.\n\n");
	

	fprintf(fptr,"----STUDENT(S) WITH MAX CGPA----\n\n");
	max_cgpa=getStudentMaxCGPA(student,count,&max_cgpa_count);
	for(int i=0;i<max_cgpa_count;i++){
		fprintf(fptr,"Roll Number: %s\n",student[max_cgpa[i]].roll_no);
		fprintf(fptr,"Name: %s\n",student[max_cgpa[i]].name);
		fprintf(fptr,"DOB: %s\n",student[max_cgpa[i]].dob);
		fprintf(fptr,"CGPA: %.1f\n\n",student[max_cgpa[i]].cgpa);
	}
	
	fprintf(fptr,"----YOUNGEST STUDENT----\n\n");
	youngest=getYoungestStudent(student,count);
	fprintf(fptr,"Roll Number: %s\n",youngest.roll_no);
	fprintf(fptr,"Name: %s\n",youngest.name);
	fprintf(fptr,"DOB: %s\n",youngest.dob);
	fprintf(fptr,"CGPA: %.1f\n\n",youngest.cgpa);

	fprintf(fptr,"----STUDENT LIST SORTED ACCORDING TO ROLL NUMBER----\n\n");
	for(int i=0;i<count;i++){
		fprintf(fptr,"Roll Number: %s\n",sorted[i].roll_no);
		fprintf(fptr,"Name: %s\n",sorted[i].name);
		fprintf(fptr,"DOB: %s\n",sorted[i].dob);
		fprintf(fptr,"CGPA: %.1f\n\n",sorted[i].cgpa);
	}

	fclose(fptr);

	char search[10];
	int index,comparisons;
	printf("Enter roll number to search (0 to exit): ");
	scanf("%s",search);
	while(strncmp(search,"0",1)!=0){
		comparisons=getRecord(sorted,count,search,&index);
		if(comparisons>0){
			printf("Record found after %d comparisons.\n",comparisons);
			printf("Roll Number: %s\n",sorted[index].roll_no);
			printf("Name: %s\n",sorted[index].name);
			printf("DOB: %s\n",sorted[index].dob);
			printf("CGPA: %.1f\n\n",sorted[index].cgpa);
		}
		else
			printf("No such record found.\n\n");

		printf("Enter roll number to search (0 to exit): ");
		scanf("%s",search);
	}
	printf("Bye!\n");
	
	return 0;
}
