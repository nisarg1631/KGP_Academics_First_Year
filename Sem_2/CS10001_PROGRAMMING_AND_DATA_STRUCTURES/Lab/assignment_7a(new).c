/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Student record program*/

#include <stdio.h>

typedef struct{
	char name[30];
	int roll_no, marks[3], total;
}stud;

stud class[20];
int count=0,roll=1;

int bin_search(int x){
	int lo=0,hi=count-1,mid;
	while(hi>=lo){
		mid=(hi+lo)/2;
		if(class[mid].roll_no==x){
			return mid;
		}
		else{
			if(x<class[mid].roll_no){
				hi=mid-1;
			}
			else{
				lo=mid+1;
			}
		}
	}
	return -1;
}

void sort_score(){
	int flag;
	stud temp;
	for(int i=0;i<count-1;i++){
		flag=0;
		for(int j=0;j<count-1-i;j++){
			if(class[j].total>class[j+1].total){
				temp=class[j];
				class[j]=class[j+1];
				class[j+1]=temp;
				flag=1;
			}
		}
		if(flag==0){
			break;
		}
	}
}

void sort_roll(){
	int flag;
	stud temp;
	for(int i=0;i<count-1;i++){
		flag=0;
		for(int j=0;j<count-1-i;j++){
			if(class[j].roll_no>class[j+1].roll_no){
				temp=class[j];
				class[j]=class[j+1];
				class[j+1]=temp;
				flag=1;
			}
		}
		if(flag==0){
			break;
		}
	}
}

void add_rec(){
	if(count==20){
		printf("Maximum record size reached. Please delete or update an existing record.\n");
	}
	else{
		printf("Name: ");
		scanf("%[^\n]", class[count].name);
		printf("Marks in Maths: ");
		scanf("%d",&class[count].marks[0]);
		printf("Marks in Physics: ");
		scanf("%d",&class[count].marks[1]);
		printf("Marks in Chemistry: ");
		scanf("%d",&class[count].marks[2]);
		class[count].total=class[count].marks[0]+class[count].marks[1]+class[count].marks[2];
		class[count].roll_no=roll++;
		count++;
	}
}

void del_rec(int r_num){
	sort_roll();
	int flag=bin_search(r_num);
	if(flag==-1){
		printf("Roll number does not exist.\n");
	}
	else{
		for(int i=flag;i<count-1;i++){
			class[i]=class[i+1];
		}
		count--;
		printf("Record deleted.\n");
	}
}

void upd_rec(int r_num){
	sort_roll();
	int flag=bin_search(r_num);
	if(flag==-1){
		printf("Roll number does not exist.\n");
	}
	else{
		printf("Name: ");
		scanf("%[^\n]", class[flag].name);
		printf("Marks in Maths: ");
		scanf("%d",&class[flag].marks[0]);
		printf("Marks in Physics: ");
		scanf("%d",&class[flag].marks[1]);
		printf("Marks in Chemistry: ");
		scanf("%d",&class[flag].marks[2]);
		class[flag].total=class[flag].marks[0]+class[flag].marks[1]+class[flag].marks[2];
		printf("Record updated.\n");
	}
}

void view_rec(){
	printf("-----------------------------------------------\n");
	for(int i=0;i<count;i++){
			printf("Roll number: %d\n",class[i].roll_no);
			printf("Name: %s\n",class[i].name);
			printf("Marks in Maths: %d, ",class[i].marks[0]);
			printf("Marks in Physics: %d, ",class[i].marks[1]);
			printf("Marks in Chemistry: %d\n",class[i].marks[2]);
			printf("Total marks: %d\n",class[i].total );
			printf("-----------------------------------------------\n");
		}
}

void avg_score(int r_num){
	sort_roll();
	int flag=bin_search(r_num);
	if(flag==-1){
		printf("Roll number does not exist.\n");
	}
	else{
		float avg=(float)class[flag].total/3;
		printf("Average marks: %.2f\n",avg);
	}
}

void max_score(){
	int max=-1,index;
	for(int i=0;i<count;i++){
			if(class[i].total>max){
				max=class[i].total;
				index=i;
			}
	}
	printf("------------Student with MAX score------------\n");
	printf("Roll number: %d\n",class[index].roll_no);
	printf("Name: %s\n",class[index].name);
	printf("Total marks: %d\n",class[index].total);
	printf("-----------------------------------------------\n");
}

void min_score(){
	int min=9999,index;
	for(int i=0;i<count;i++){
			if(class[i].total<min){
				min=class[i].total;
				index=i;
			}
	}
	printf("------------Student with MIN score------------\n");
	printf("Roll number: %d\n",class[index].roll_no);
	printf("Name: %s\n",class[index].name);
	printf("Total marks: %d\n",class[index].total);
	printf("-----------------------------------------------\n");
}

void max_score_sub(int x){
	int max=-1,index;
	for(int i=0;i<count;i++){
			if(class[i].marks[x]>max){
				max=class[i].marks[x];
				index=i;
			}
	}
	printf("--Student with MAX score in selected subject--\n");
	printf("Roll number: %d\n",class[index].roll_no);
	printf("Name: %s\n",class[index].name);
	printf("Marks in selected subject: %d\n",class[index].marks[x]);
	printf("-----------------------------------------------\n");
}

int main(){

	int opt;

	while(1){
		printf("Choose operation from given list:\n");
		printf("1> Add student records\n");
		printf("2> Delete student records (by roll number)\n");
		printf("3> Update student records\n");
		printf("4> View all student records\n");
		printf("5> Calculate an average of a selected student’s scores\n");
		printf("6> Show student who gets the max total score\n");
		printf("7> Show student who gets the min total score\n");
		printf("8> Find student by ID\n");
		printf("9> Sort records by total scores\n");
		printf("10> Identify the student who got highest marks in a given subject.\n");
		printf("11> Exit\n");

		scanf("%d",&opt);

		if(opt==1){
			fflush(stdin);
			add_rec();
		}

		else if(opt==2){
			int temp;
			printf("Enter roll number to delete: ");
			scanf("%d",&temp);
			del_rec(temp);
		}

		else if(opt==3){
			int temp;
			printf("Enter roll number to update details: ");
			scanf("%d",&temp);
			fflush(stdin);
			upd_rec(temp);
		}

		else if(opt==4){
			view_rec();
		}

		else if(opt==5){
			int temp;
			printf("Enter roll number: ");
			scanf("%d",&temp);
			avg_score(temp);
		}

		else if(opt==6){
			max_score();
		}

		else if(opt==7){
			min_score();
		}

		else if(opt==8){
			int temp;
			printf("Enter roll number to search: ");
			scanf("%d",&temp);
			sort_roll();
			int search=bin_search(temp);
			if(search==-1)
				printf("No record found at given roll number.\n");
			else{
				printf("Name: %s\n",class[search].name);
			}
		}

		else if(opt==9){
			sort_score();
		}

		else if(opt==10){
			int temp;
			printf("Enter subject number to search (0 for Maths, 1 for Physics, 2 for Chemistry): ");
			scanf("%d",&temp);
			max_score_sub(temp);
		}

		else if(opt==11){
			printf("Bye\n");
			break;
		}
	}

	return 0;
}
