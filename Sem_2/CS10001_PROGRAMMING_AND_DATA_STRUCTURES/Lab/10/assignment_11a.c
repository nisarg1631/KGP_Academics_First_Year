/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 11(a)*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char name1[30],name2[30];
	float unit_price;
}_MENU;

_MENU * readFile(int *count){
	FILE *fptr=fopen("menu.txt","r");
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		exit(-1);
	}
	else
		printf("Input file successfully loaded.\n");
	
	char buffer;
	fscanf(fptr,"%d",count);
	_MENU *menu=(_MENU *)malloc((*count)*sizeof(_MENU));
	
	for(int i=0;i<(*count);i++)
		fscanf(fptr,"%s %s %f",menu[i].name1,menu[i].name2,&menu[i].unit_price);

	fclose(fptr);
	return menu;
}

void writeFile(_MENU *menu, int count){
	FILE *fptr=fopen("menu_tax.txt","w");
	if(fptr==NULL){
		printf("Error in output file creation.\n");
		exit(-1);
	}
	else
		printf("Output file successfully created.\n");

	for(int i=0;i<count;i++)
		fprintf(fptr,"%2d> %s %s %.2f\n",i+1,menu[i].name1,menu[i].name2,(menu[i].unit_price*115)/100);

	fclose(fptr);
}

int main(){
	int item_count;
	_MENU *menu;
	
	menu=readFile(&item_count);
	writeFile(menu,item_count);
	
	return 0;
}