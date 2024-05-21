/************************************************
*
*Name			: Saiyam Sharma				*
*Roll No.		: 19MI31019			    	*
*Program		: 04						*
*Date			: 13-05-2020				*
*Acknowledgements	: citations/references	*
*************************************************/

#include <stdio.h>
#include <stdlib.h>

// function to extract integer values from file
int getint(FILE *f)
{
  int ret = 0;
  char c = fgetc(f);
  while(c > 47 && c < 58)  // loop will end when non-integer value found ex. [space] [Tab] or [new line]
  {
    ret = ret*10 + c-48;
    c = fgetc(f);
  }
  return ret;   // returns the integer
}

int main()
{
  char fname[20];
  printf("Enter file name: ");
  scanf("%s",fname);         // taking filename input


  FILE* f = fopen(fname,"r"); //opening file in read mode
  int m = getint(f);
  int n = getint(f);          
  int *S[m];                  // array of pointers (for 2D dynamic array allocation)

  for(int i=0;i<m;i++)
    S[i] = (int *)malloc(n*sizeof(int));
    
  for(int i=0;i<m;i++)       // filing up array S from input file
  {
    for(int j=0;j<n;j++)
      S[i][j] = fgetc(f)-48;
    fgetc(f);
  }

  fclose(f);                //closing file



  for(int i=0;i<m;i++)   // printing array S
  {
    for(int j=0;j<n;j++)
      printf("%d",S[i][j]);
    printf("\n");
  }


  printf("Videos liked by atleast 50%% of the members:");
  for(int i=0;i<n;i++)
  {
    int cnt = 0;               //counts number of member liked ith video
    for(int j=0;j<m;j++)
    {
      if(S[j][i])
        cnt++;
    }
    if(cnt >= (m+1)/2)        // checking condition for 50%
      printf("V%d ",i+1);
  }
  printf("\n");

  //####### LEAST LIKED VIDEO ########

  int likes = 10000000,member = 0;     
  for(int i=0;i<m;i++)
  {
    int cnt = 0;       // counts no. of likes by particular member
    for(int j=0;j<n;j++)
      cnt += S[i][j];
    if(cnt < likes)
    {
      likes = cnt;
      member = i+1;
    }
  }
  printf("Member with least #likes = M%d (#likes = %d)\n",member,likes);


  // ########### RECOMMENDATIONS ##########

  printf("Recommended videos: ");

  int a[n];           // array to keep trrack of which video to recommend
  for(int i=0;i<n;i++)
    a[i] = 0;

  for(int i=0;i<n;i++)   // checking all conditions
    if(S[member-1][i])
      for(int j=0;j<m;j++)
        if(S[j][i])
          for(int k=0;k<n;k++)
            if(S[j][k])
              a[k] = 1;

  for(int i=0;i<n;i++)  // printing all recommendations
  {
    if(a[i] && !S[member-1][i])
      printf("V%d, ",i+1);
  }
  printf("\n");
  return 0;
}