#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 99999
#define MIN_SIZE -1

typedef struct ll_node{
	int rank,pop,n_change,pop_den;
    float y_change;
    char name[30];
    struct ll_node *next;
}node;

//hash function to find hash code through given method
int hash(char input[]){
    int sum=0;
    for(int i=0;i<strlen(input);i++)
        sum+=(int)input[i];
    return (sum%7);
}

//allocates memory for a new node and stores the data given as input, adds the node to the list according to hash value
void insert_node(node **head, node input){
    int list_index=hash(input.name);
    node *new_node=(node *)malloc(sizeof(node));
    *new_node=input;

	if(head[list_index]==NULL)
        head[list_index]=new_node;
    else{
        node *it=head[list_index];
        while(it->next!=NULL)
            it=it->next;
        it->next=new_node;
    }
}

//reads data from file in a loop and uses insert_node function to store it in linked list
node **readCountryData(int list_length[]){
	FILE *fptr=fopen("CountryStat.txt","r");
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		exit(-1);
	}

	node **head=(node **)malloc(7*sizeof(node *));
    for(int i=0;i<7;i++)
        head[i]=NULL;
    
    node temp;
    char buff;
	while(!feof(fptr)){
		fscanf(fptr,"%d",&(temp.rank));
        fgetc(fptr);
		fscanf(fptr,"%[^\n]",temp.name);
        fgetc(fptr);
		fscanf(fptr,"%d",&(temp.pop));
		fscanf(fptr,"%f",&(temp.y_change));
		fscanf(fptr,"%d",&(temp.n_change));
		fscanf(fptr,"%d",&(temp.pop_den));
        temp.next=NULL;
        insert_node(head,temp);
        list_length[hash(temp.name)]++;
    }

	fclose(fptr);
	return head;
}

//searches for the search string in corresponding hash list, returns pointer to node if found else returns NULL 
node *searchByName(node **head, char search[]){
    node *it=head[hash(search)];   //it: iterator for traversing the corresponding hash list
    while(it!=NULL){
        if(strncmp(it->name,search,strlen(search))==0)
            return it;
        it=it->next;
    }
    return NULL;
}

//gets the next minimum value by iterating through all lists, returns MAX_SIZE if not found (all elements covered), mode=1 for population density minimum, mode=2 for net change minimum
int getNextMin(node **head, int prev_min, int mode){
    int min=MAX_SIZE;
    for(int i=0;i<7;i++){
        node *it=head[i];   //it: iterator for traversing the corresponding hash list
        while(it!=NULL){
            if(mode==1){
                if((it->pop_den<min)&&(it->pop_den>prev_min))
                    min=it->pop_den;
            }
            else if(mode==2){
                if((it->n_change<min)&&(it->n_change>prev_min))
                    min=it->n_change;
            }
            it=it->next;
        }
    }
    return min;
}

//gets the next maximum value of population by iterating through all lists, returns MIN_SIZE if not found (all elements covered)
int getNextMax(node **head, int prev_max){
    int max=MIN_SIZE;
    for(int i=0;i<7;i++){
        node *it=head[i];   //it: iterator for traversing the corresponding hash list
        while(it!=NULL){
            if((it->pop>max)&&(it->pop<prev_max))
                max=it->pop;
            it=it->next;
        }
    }
    return max;
}

//gets the next maximum value (float) of yearly change by iterating through all lists, returns MIN_SIZE if not found (all elements covered)
float getNextMax_float(node **head, float prev_max){
    float max=(float)MIN_SIZE;
    for(int i=0;i<7;i++){
        node *it=head[i];   //it: iterator for traversing the corresponding hash list
        while(it!=NULL){
            if((it->y_change>max)&&(it->y_change<prev_max))
                max=it->y_change;
            it=it->next;
        }
    }
    return max;
}

//prints all occurences of a particular value found in all the lists according to mode, mode=1 for population density, mode=2 for net change, mode=3 for population, mode=4 for yearly change, yearly change uses float_value, left float_value to be 0 for other modes
void printAllOccurences(node **head, int value, float float_value, int mode){
    for(int i=0;i<7;i++){
        node *it=head[i];   //it: iterator for traversing the corresponding hash list
        while(it!=NULL){
            if(mode==1){
                if((it->pop_den)==value){
                    printf("->%s\n",it->name);
                    printf("Population density (person/sq. km): %d\n\n",it->pop_den);
                }
            }
            else if(mode==2){
                if((it->n_change)==value){
                    printf("->%s\n",it->name);
                    printf("Net change (thousands): %d\n\n",it->n_change);
                }
            }
            else if(mode==3){
                if((it->pop)==value){
                    printf("->%s\n",it->name);
                    printf("Rank: %d\n",it->rank);
                    printf("Population (millions): %d\n\n",it->pop);
                }
            }
            else if(mode==4){
                if((it->y_change)==float_value){
                    printf("->%s\n",it->name);
                    printf("Yearly change (%%) %.2f\n\n",it->y_change);
                }
            }
            it=it->next;
        }
    }
}

//increases rank of all countries whose population is less than input city by 1, this frees a rank which is assigned to input city
int getNewRank(node **head, node new_node){
    int total=0, below=0;
    for(int i=0;i<7;i++){
        node *it=head[i];   //it: iterator for traversing the corresponding hash list
        while(it!=NULL){
            total++;
            if(it->pop<new_node.pop){
                below++;
                (it->rank)++;
            }
            it=it->next;
        }
    }
    return (total-below+1);
}

int main(){
    int list_length[7]={0};     //list_length array stores the length of each list
    node **DATA=readCountryData(list_length);   //DATA is array of head nodes of all lists, can be accessed by DATA[0], DATA[1], etc.
    
    //printing each of the 7 lists and their lengths
    for(int i=0;i<7;i++){
        node *it=DATA[i];
        printf("----LIST %d, LENGTH=%d----\n\n",i,list_length[i]);
        while(it!=NULL){
            printf("->%s\n",it->name);
            printf("Rank: %d\n",it->rank);
            printf("Population (millions): %d\n",it->pop);
            printf("Population density (person/sq. km): %d\n",it->pop_den);
            printf("Yearly change (%%): %.2f\n",it->y_change);
            printf("Net change (thousands): %d\n\n",it->n_change);
            it=it->next;
        }
        printf("\n");
    }

    int opt;

    while(1){   //menu driven program to perform operations on linked list
        printf("\nChoose operation from given list:\n"  //menu options
		    "1> Insert new record\n"
		    "2> Get statistics from name\n"
		    "3> Get population rank from name\n"
		    "4> Country with lowest population density\n"
		    "5> Country with highest yearly change\n"
		    "6> List countries in descending order of population\n"
		    "7> List countries in descending order of yearly change\n"
		    "8> List countries in ascending order of population density\n"
		    "9> List countries in ascending order of net change\n"
		    "10> Exit\n"
            ">> ");
            scanf("%d",&opt);
            getchar();
        
        if(opt==1){     //country name is taken as input from user
            node temp;
            printf("Enter country name: ");
            scanf("%[^\n]",temp.name);
            getchar();
            node *found=searchByName(DATA,temp.name);
            if(found==NULL){       //if country name is not found then user is asked for statistics
                printf("Enter population (millions): ");
                scanf("%d",&(temp.pop));
                printf("Enter yearly change (%%): ");
                scanf("%f",&(temp.y_change));
                printf("Enter net change (thousands): ");
                scanf("%d",&(temp.n_change));
                printf("Enter population density (person/sq. km): ");
                scanf("%d",&(temp.pop_den));
                temp.next=NULL;
                temp.rank=getNewRank(DATA,temp);
                insert_node(DATA,temp);
                list_length[hash(temp.name)]++;
            }
            else{       //if country is found then its statistics are printed
                printf("Rank: %d\n",found->rank);
                printf("Population (millions): %d\n",found->pop);
                printf("Population density (person/sq. km): %d\n",found->pop_den);
                printf("Yearly change (%%): %.2f\n",found->y_change);
                printf("Net change (thousands): %d\n",found->n_change);
            }
        }

        else if(opt==2){
            char temp[30];
            printf("Enter country name: ");
            scanf("%[^\n]",temp);
            getchar();
            node *found=searchByName(DATA,temp);
            if(found==NULL)
                printf("Record not found\n");
            else{
                printf("Rank: %d\n",found->rank);
                printf("Population (millions): %d\n",found->pop);
                printf("Population density (person/sq. km): %d\n",found->pop_den);
                printf("Yearly change (%%): %.2f\n",found->y_change);
                printf("Net change (thousands): %d\n",found->n_change);
            }
        }
        
        else if(opt==3){
            char temp[30];
            printf("Enter country name: ");
            scanf("%[^\n]",temp);
            getchar();
            node *found=searchByName(DATA,temp);
            if(found==NULL)
                printf("Record not found\n");
            else
                printf("Rank: %d\n",found->rank);
        }

        else if(opt==4){
            printAllOccurences(DATA,getNextMin(DATA,MIN_SIZE,1),0,1);     //print the first minimum value of population density
        }

        else if(opt==5){
            printAllOccurences(DATA,0,getNextMax_float(DATA,(float)MAX_SIZE),4);     //print the firts maximum value of yearly change
        }

        else if(opt==6){
            printf("----COUNTRIES IN DESCENDING ORDER OF POPULATION----\n\n");
            int max=MAX_SIZE;
            do{
                max=getNextMax(DATA,max);
                printAllOccurences(DATA,max,0,3);
            }while(max!=MIN_SIZE);      //keep printing next maximum value (descending order) until complete list is exhausted
        }

        else if(opt==7){
            printf("----COUNTRIES IN DESCENDING ORDER OF YEARLY CHANGE----\n\n");
            float max=(float)MAX_SIZE;
            do{
                max=getNextMax_float(DATA,max);
                printAllOccurences(DATA,0,max,4);
            }while(max!=MIN_SIZE);      //keep printing next maximum value (descending order) until complete list is exhausted
        }

        else if(opt==8){
            printf("----COUNTRIES IN ASCENDING ORDER OF POPULATION DENSITY----\n\n");
            int min=MIN_SIZE;
            do{
                min=getNextMin(DATA,min,1);
                printAllOccurences(DATA,min,0,1);
            }while(min!=MAX_SIZE);      //keep printing next minimum value (ascending order) until complete list is exhausted
        }

        else if(opt==9){
            printf("----COUNTRIES IN ASCENDING ORDER OF NET CHANGE----\n\n");
            int min=MIN_SIZE;
            do{
                min=getNextMin(DATA,min,2);
                printAllOccurences(DATA,min,0,2);
            }while(min!=MAX_SIZE);      //keep printing next minimum value (ascending order) until complete list is exhausted
        }
        
        else if(opt==10){
            printf("Program terminated\n");
            break;
        }
        
        else
            printf("Invalid option\n");
    }
    return 0;
}