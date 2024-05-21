/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 11(b)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	char search[30];
	printf("Search item to buy: ");
	scanf("%s",search);

	int *serial=(int *)malloc(item_count*sizeof(int));
	int num=0;
	for(int i=0;i<item_count;i++){
		if(strcasecmp(search,menu[i].name1)==0||strcasecmp(search,menu[i].name2)==0)
			serial[num++]=i;
	}
	if(num==0)
		printf("No such item found.\n");
	else{
		float cost=0;
		printf("%d item(s) found:\n",num);
		for(int i=0;i<num;i++)
			printf("%2d> %s %s %.2f\n",serial[i]+1,menu[serial[i]].name1,menu[serial[i]].name2,(menu[serial[i]].unit_price*115)/100);
		printf("---Place your order by serial number (enter 0 to complete purchase)---\n");
		while(1){
			int itm,qty,found;
			printf("Enter serial number: ");
			scanf("%d",&itm);

			if(itm==0){
				printf("Total amount: %.2f\nBye!\n",cost);
				break;
			}
			else{
				found=0;
				for(int i=0;i<num;i++){
					if(serial[i]+1==itm){
						found=1;
						break;
					}
				}

				if(found==0)
					printf("Enter valid serial number from above list.\n");
				else{
					printf("Enter quantity: ");
					scanf("%d",&qty);
					cost+=((menu[itm-1].unit_price*115)/100)*qty;
					printf("Current amount: %.2f\n",cost);
				}
			}
		}
	}
	return 0;
}