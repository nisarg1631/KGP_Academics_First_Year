#include <stdio.h>

typedef struct{
	char sym;
	int num,index;
	float weight;
}atom;

typedef struct{
	int n;
	atom elem[100];
	int atmcnt[100];
}molecule;

float molecularwt(molecule m){
	float m_weight=0;
	for(int i=0;i<m.n;i++){
		m_weight+=((m.elem[i].weight)*(m.atmcnt[i]));
	}
	return m_weight;
}

int isbalanced(molecule l1, molecule l2, molecule r1, molecule r2){
	int left[4]={0},right[4]={0};

	for(int i=0;i<l1.n;i++){
		left[l1.elem[i].index]+=l1.atmcnt[i];
	}
	for(int i=0;i<l2.n;i++){
		left[l2.elem[i].index]+=l2.atmcnt[i];
	}
	for(int i=0;i<r1.n;i++){
		right[r1.elem[i].index]+=r1.atmcnt[i];
	}
	for(int i=0;i<r2.n;i++){
		right[r2.elem[i].index]+=r2.atmcnt[i];
	}

	for(int i=0;i<4;i++){
		if(left[i]!=right[i])
			return 0;
	}
	return 1;
}

int main(){
	atom element[4];
	molecule compound[4];

	printf("#### Provide element data ####\n");
	for(int i=0;i<4;i++){
		printf("Enter character for %d element: ",i+1);
		scanf("%c",&element[i].sym);
		printf("Enter atomic number for %d element: ",i+1);
		scanf("%d",&element[i].num);
		printf("Enter molecular weight for %d element: ",i+1);
		scanf("%f",&element[i].weight);
		element[i].index=i;
		fflush(stdin);
	}

	int i=0;
	printf("#### Provide compound data ####\n");
	printf("Use the following element codes to add element to compound:\n");
	printf("1->%c\n",element[0].sym);
	printf("2->%c\n",element[1].sym);
	printf("3->%c\n",element[2].sym);
	printf("4->%c\n",element[3].sym);
	while(i<4){
		printf("Enter number of elements in %d compound (less than or equal to 4): ",i+1);
		scanf("%d",&compound[i].n);
		for(int j=0;j<compound[i].n;j++){
			int temp;
			printf("Enter %d element code: ",j+1);
			scanf("%d",&temp);
			compound[i].elem[j]=element[temp-1];
			printf("Enter atom count of %d element: ",j+1);
			scanf("%d",&temp);
			compound[i].atmcnt[j]=temp;
		}
		i++;
	}

	i=0;
	printf("#### Molecular weights ####\n");
	while(i<4){
		printf("Compound %d constituents: ",i+1);
		for(int j=0;j<compound[i].n;j++){
			printf("%c%d ",compound[i].elem[j].sym,compound[i].atmcnt[j]);
		}
		printf("\nCompound %d weight: %.2f\n",i+1,molecularwt(compound[i]));
		i++;
	}

	printf("#### Reaction l1+l2-->r1+r2 ####\n");
	molecule l1,l2,r1,r2;
	int temp;
	printf("Enter compound code for l1: ");
	scanf("%d",&temp);
	l1=compound[temp-1];
	printf("Enter compound code for l2: ");
	scanf("%d",&temp);
	l2=compound[temp-1];
	printf("Enter compound code for r1: ");
	scanf("%d",&temp);
	r1=compound[temp-1];
	printf("Enter compound code for r2: ");
	scanf("%d",&temp);
	r2=compound[temp-1];

	if(isbalanced(l1,l2,r1,r2)==0)
		printf("Equation not balanced\n");
	else
		printf("Equation is balanced\n");

	return 0;
}
