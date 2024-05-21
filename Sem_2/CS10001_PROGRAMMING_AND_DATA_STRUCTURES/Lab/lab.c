#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//point structure
typedef struct _POINTF{
	float x,y;
}Pointf;

//structure for a linesegment
typedef struct _LINESEG{
	Pointf p1,p2;
}Lineseg;

//structure for list of points
typedef struct _POINTLIST{
	Pointf *p;
	int size;
}Pointlist;

Pointf intersectpoint(Lineseg l1, Lineseg l2){
	Pointf answer;
	float a[3],b[3];

	a[0]=l1.p2.y-l1.p1.y;
	a[1]=l1.p1.x-l1.p2.x;
	a[2]=l1.p1.x*(a[0])+l1.p1.y*(a[1]);

	b[0]=l2.p2.y-l2.p1.y;
	b[1]=l2.p1.x-l2.p2.x;
	b[2]=l2.p1.x*(a[0])+l2.p1.y*(a[1]);

	answer.x=(a[2]*b[1]-a[1]*b[2])/(a[0]*b[1]-a[1]*b[0]);
	answer.y=(a[0]*b[2]-a[2]*b[0])/(a[0]*b[1]-a[1]*b[0]);

	return answer;
}

int intersects(Lineseg l1, Lineseg l2){
	float dx_1, dy_1, dx_2, dy_2, m1, m2;

	dx_1=l1.p1.x-l1.p2.x;
	dy_1=l1.p1.y-l1.p2.y;
	dx_2=l2.p1.x-l2.p2.x;
	dy_2=l2.p1.y-l2.p2.y;

	m1=(dy_1/dx_1);
	m2=(dy_2/dx_2);

	float l1_xlimit[2], l1_ylimit[2], l2_xlimit[2], l2_ylimit[2];
		if(l1.p1.x>l1.p2.x){
			l1_xlimit[0]=l1.p2.x;
			l1_xlimit[1]=l1.p1.x;
		}
		else{
			l1_xlimit[0]=l1.p1.x;
			l1_xlimit[1]=l1.p2.x;
		}
		if(l1.p1.y>l1.p2.y){
			l1_ylimit[0]=l1.p2.y;
			l1_ylimit[1]=l1.p1.y;
		}
		else{
			l1_ylimit[0]=l1.p1.y;
			l1_ylimit[1]=l1.p2.y;
		}
		if(l2.p1.x>l2.p2.x){
			l2_xlimit[0]=l2.p2.x;
			l2_xlimit[1]=l2.p1.x;
		}
		else{
			l2_xlimit[0]=l2.p1.x;
			l2_xlimit[1]=l2.p2.x;
		}
		if(l2.p1.y>l2.p2.y){
			l2_ylimit[0]=l2.p2.y;
			l2_ylimit[1]=l2.p1.y;
		}
		else{
			l2_ylimit[0]=l2.p1.y;
			l2_ylimit[1]=l2.p2.y;
		}

	if((m1-m2)<(float)1e-6){
		return 0;
	}
	else{
		Pointf inter=intersectpoint(l1,l2);
		if(((inter.x>=l1_xlimit[0])&&(inter.x<=l1_xlimit[1]))&&((inter.x>=l2_xlimit[0])&&(inter.x<=l2_xlimit[1]))){
			if(((inter.y>=l1_ylimit[0])&&(inter.y<=l1_ylimit[1]))&&((inter.y>=l2_ylimit[0])&&(inter.y<=l2_ylimit[1]))){
				return 1;
			}
		}
		else{
			return 0;
		}		
	}
}

Lineseg genls(){
	Lineseg answer;

	answer.p1.x=(rand()*(1.0))/RAND_MAX;
	answer.p1.y=(rand()*(1.0))/RAND_MAX;
	answer.p2.x=(rand()*(1.0))/RAND_MAX;
	answer.p2.y=(rand()*(1.0))/RAND_MAX;

	return answer;
}

void printls(Lineseg lseg){
	printf("(%f,%f) (%f,%f)\n",lseg.p1.x,lseg.p1.y,lseg.p2.x,lseg.p2.y);
}

int countintpt (Lineseg llist[]){
	int count=0;
	for(int i=0;i<10;i++){
		for(int j=i+1;j<10;j++){
			if(intersects(llist[i],llist[j]))
				count++;
		}
	}
	return count;
}

void createplist(Lineseg llist [], Pointlist *pplist, int num){
	pplist->p=(Pointf *)malloc(num*sizeof(Pointf));
	pplist->size=num;
	int count=0;
	for(int i=0;i<10;i++){
		for(int j=i+1;j<10;j++){
			if(intersects(llist[i],llist[j])){
				(pplist->p)[count++]=intersectpoint(llist[i],llist[j]);
			}	
		}
	}
}

void printall(Pointlist plist){
	for(int i=0;i<plist.size;i++){
		printf("(%f,%f)\n",(plist.p)[i].x , (plist.p)[i].y);
	}
}

int main(){
	srand(time(NULL));
	Pointlist Plist;
  	Lineseg LSarr[10];
  	
	int i=0;
	while(i<10){
  		LSarr[i]=genls();
		i++;
  	}

	printf("Line Segments Array:\n");
	for(int i=0;i<10;i++){
		printls(LSarr[i]);
	}
	printf("\n");
  	
	int num=countintpt(LSarr);
  	createplist(LSarr,&Plist,num);

	printf("Intersection Points:\n");
  	printall(Plist);
	return 0;
}