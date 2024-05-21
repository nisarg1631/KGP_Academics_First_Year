#include <stdio.h>
#define maxsize 100

int getdigits(int x, int digits[])
{
  int n=0;
  for (int i = 0; x!=0; i++)
  {
    digits[i]=x%10;
    x=x/10;
    n++;
  }
  return n;
}

void encrypt(char inputS[], int x, char outputS[])
{
  int n_digits,digits[maxsize];
  n_digits=getdigits(x,digits);

  int i=0,j=0;
  while(inputS[i]!='\0'){
    if(inputS[i]>='A'&&inputS[i]<='Z'){
      outputS[i]='A'+((inputS[i]+digits[j]-'A')%26);
    }
    else if(inputS[i]>='a'&&inputS[i]<='z'){
      outputS[i]='a'+((inputS[i]+digits[j]-'a')%26);
    }
    i++;
    if(j!=n_digits-1)
      j++;
    else
      j=0;
  }
  outputS[i]='\0';
}

void decrypt(char inputS[], int x, char outputS[])
{
  int n_digits,digits[maxsize];
  n_digits=getdigits(x,digits);

  int i=0,j=0;
  while(inputS[i]!='\0'){
    if(inputS[i]>='A'&&inputS[i]<='Z'){
      outputS[i]='Z'-(('Z'-inputS[i]+digits[j])%26);
    }
    else if(inputS[i]>='a'&&inputS[i]<='z'){
      outputS[i]='z'-(('z'-inputS[i]+digits[j])%26);
    }
    i++;
    if(j!=n_digits-1)
      j++;
    else
      j=0;
  }
  outputS[i]='\0';
}

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
  char inputS[maxsize], encryptS[maxsize][maxsize], decryptS[maxsize][maxsize], words[maxsize][maxsize];
  int x;

  printf("Enter string to be encrypted:");
  scanf("%[^\n]",inputS);
  printf("Enter the encryption key:");
  scanf("%d",&x);

  int n=ConvertWords(inputS, words), count=0;

  for (int i = 0; i < n; i++)
  {
    if(words[i][0]!='\0'){
      encrypt(words[i],x,encryptS[count]);
      count++;
    }
  }
  for (int i = 0; i < count; i++)
  {
      decrypt(encryptS[i],x,decryptS[i]);
  }

  printf("Encrypted: ");
  for (int i = 0; i < count; i++)
    printf("%s ",encryptS[i]);
  printf("\n");
  printf("Decrypted: ");
  for (int i = 0; i < count; i++)
    printf("%s ",decryptS[i]);
  printf("\n");

  return 0;
}
