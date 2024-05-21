/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Lab Test 2 - 3e*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _STUDENT{
	char name[11],group[6];
	float marks;
}student;

student *readFile(int *count){
	FILE *fptr=fopen("t3e.txt","r");
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		exit(-1);
	}
	else
		printf("Input file successfully loaded.\n");
	
	fscanf(fptr,"%d",count);
	student *data=(student *)malloc((*count)*sizeof(student));
	
	for(int i=0;i<(*count);i++){
		fscanf(fptr,"%s %s %f",data[i].name,data[i].group,&data[i].marks);
		fgetc(fptr);
	}

	fclose(fptr);
	return data;
}

int main(){
	int student_count;
	float max_marks=-1;
	student *student_arr=readFile(&student_count), best_girl;
	
	for(int i=0;i<student_count;i++){
		printf("%s %s - %.2f\n",student_arr[i].name,student_arr[i].group,student_arr[i].marks);
		if(strcmp(student_arr[i].group,"girl")==0){
			if(student_arr[i].marks>max_marks){
				max_marks=student_arr[i].marks;
				best_girl=student_arr[i];
			}
		}
	}
	printf("Best girl student: %s.\n",best_girl.name);
	
	return 0;
}