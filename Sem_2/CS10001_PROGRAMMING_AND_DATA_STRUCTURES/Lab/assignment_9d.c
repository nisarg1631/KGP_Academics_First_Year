/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Dynamic memory allocation for 1D structure array (9d)*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int width,height;
}rectangle;

void swap(rectangle *r1, rectangle *r2){
	rectangle temp;
	temp=*r1;
	*r1=*r2;
	*r2=temp;
}

void bubble_sort(rectangle *r, int size){
	int flag;
	for(int i=0;i<size;i++){
		flag=0;
		for(int j=0;j<size-i-1;j++){
			if((r[j].width*r[j].height)>(r[j+1].width*r[j+1].height)){
				swap(r+j,r+j+1);
				flag=1;
			}
		}
		if(flag==0)
			return;
	}
}

int main(){
	int n;
	printf("Enter n: ");
	scanf("%d",&n);

	rectangle *rect=(rectangle *)malloc(n*sizeof(rectangle));
	printf("Enter width and height of %d rectangles:\n",n);
	for(int i=0;i<n;i++)
		scanf("%d %d",&rect[i].width,&rect[i].height);

	bubble_sort(rect,n);
	printf("Sorted by area:\n");
	for(int i=0;i<n;i++)
		printf("(%d,%d) ",rect[i].width,rect[i].height);
	printf("\n");

	return 0;
}
