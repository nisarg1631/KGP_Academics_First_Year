#include <stdio.h>
#define maxsize 50

/*void ConvertWords(char inputS[], char arr[][]) {

  for (int i = 0; i < maxsize; i++) {
    if (inputS[i]=='\0' || inputS[i]==',' || inputS[i]=='?' || inputS[i]==';')
    {
      arr[j][k]=inputS[i];
      j++;
      k=0;
    }
    else
    {
      arr[j][k]=inputS[i];
      k++;
    }
  }
}
int main() {
  char inputS[maxsize];
  char outarr[maxsize][maxsize];

  printf("Enter string\n");
  gets(inputS);
  ConvertWords(inputS, outarr);
  for (int i = 0; i < maxsize; i++) {
    printf("\n");
    for (int j = 0; j < maxsize; j++) {
      printf("%c ",&outarr[i][j]);
    }
  }


  return 0;
}*/
#include <stdio.h>
#define maxsize 50

int ConvertWords(char inputS[], char arr[][maxsize]) {
int j = 0, k = 0;
  for (int i = 0; i < maxsize; i++) {
    if (inputS[i]!='\0' && inputS[i]!=',' && inputS[i]!='?' && inputS[i]!=';' && inputS[i]!=' ' && inputS[i]!='!' && inputS[i]!='.')
    {
      arr[j][k]=inputS[i];
      k++;
    }
    else
    {
      arr[j][k]='\0';
      j++;
      k=0;
    }
    if(inputS[i]=='\0')
      break;
  }
  return j;
}
int main()
{
  char inputS[maxsize];
  char outarr[maxsize][maxsize];

  printf("Enter string:");
  scanf("%[^\n]",inputS);
  int n=ConvertWords(inputS, outarr);
  for (int i = n-1; i >= 0; i--)
  {
    if(outarr[i][0]!='\0')
      printf("%s ",outarr[i]);
  }


  return 0;
}
