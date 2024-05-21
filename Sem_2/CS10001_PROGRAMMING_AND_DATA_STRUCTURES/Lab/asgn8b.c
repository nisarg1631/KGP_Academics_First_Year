#include <stdio.h>
#define MAXSIZE 100

typedef struct{
	char roll_no[10],name[100],gender;
	int age;
	float cgpa;
}_student;


void swap(_student *s1, _student *s2){
	_student temp;
	temp=*s1;
	*s1=*s2;
	*s2=temp;
}

int compute_top_cgpa(_student class[], int index[], int count){
	float max=-1;
	int top=0;
	for(int i=0;i<count;i++){
		if(class[i].cgpa>max){
			max=class[i].cgpa;
			top=0;
			index[top]=i;
			top++;
		}
		else if(class[i].cgpa==max){
			index[top]=i;
			top++;
		}
	}
	return top;
}

void store_array_of_toppers(_student class[], _student topper[], int index[], int count){
	for(int i=0;i<count;i++)
		topper[i]=class[index[i]];
}

void print_array_of_students(_student topper[], int count){
	int flag;
	for(int i=0;i<count;i++){
		flag=0;
		for(int j=0;j<count-i-1;j++){
			if(topper[j].age>topper[j+1].age){
				swap(&topper[j],&topper[j+1]);
				flag=1;
			}
		}
		if(flag==0)
			break;
	}
	printf("---LIST OF TOPPERS (in ascending order of age)---\n");
	for(int i=0;i<count;i++)
		printf("%d> %s, %s, %d, %c, %.2f\n",i+1,topper[i].roll_no,topper[i].name,topper[i].age,topper[i].gender,topper[i].cgpa);
}

int main(){

	_student class[MAXSIZE],topper[MAXSIZE];
	int top_indices[MAXSIZE], top_count,n;

	printf("N=");
	scanf("%d",&n);

	for(int i=0;i<n;i++){
		fflush(stdin);
		printf("->Enter records of %d student\n",i+1);
		printf("Roll Number: ");
		gets(class[i].roll_no);
		printf("Name: ");
		gets(class[i].name);
		printf("Age: ");
		scanf("%d",&class[i].age);
		fflush(stdin);
		printf("Gender: ");
		scanf("%c",&class[i].gender);
		printf("CGPA: ");
		scanf("%f",&class[i].cgpa);
	}

	top_count=compute_top_cgpa(class,top_indices,n);
	store_array_of_toppers(class,topper,top_indices,top_count);
	print_array_of_students(topper,top_count);

	return 0;
}
