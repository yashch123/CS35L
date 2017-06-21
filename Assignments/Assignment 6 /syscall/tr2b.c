#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int checkDuplicates(char* temp1, char* head1); //WRITE THIS FUNCTION
int checkDuplicates(char* from,char* to);
int containPosition(char* from, char ch, int n);


int checkDuplicates(char* from, char* to)
{
  int i,j;
  for(i = 0; i < from[i]!='\0'; i++)
    {
      for(j = i+1; j < to[j]!='\0'; j++)
        {
          if(from[j] == from[i])
            {
              return 1;
            }
	}
    }
  return 0;
}

int main(int argc,char *argv[])
{
  if(argc!=3)
    {
      fprintf(stderr,"Please input 2 operands\n");
      exit(1);
    }

  //Assign from and to as respective operands:

  char* from = argv[1];
  char* to = argv[2];

  //Compare lengths here:
  int n=0;
  int m=0;
  char* temp1 = from;
  char* temp2 = to;
  
  while(*(temp1)!='\0')
    {
      n++;
      temp1++;
    }
  putchar(n);
  while((*temp2)!='\0')
    {
      m++;
      temp2++;
    }
  putchar(m);
  //Check if both are of the same size:
  if(n!=m)
    {
      fprintf(stderr,"The lengths of the 2 operands must be the same\n");
      exit(1);
    }

  //Check if from has duplicate bytes:
  
  if(checkDuplicates(from,to))
    {
      fprintf(stderr,"The operand 'from' cannot have duplicate values\n");
      exit(1);
    }
  

  //Now take in using getchar and compare if that char falls in from

  int ch = getchar();
 
  while(ch!=EOF)
    {
      int pos = containPosition(from,ch,n);
      if(pos==-1)
	putchar(ch);
      else
	putchar(to[pos]);

      ch = getchar();
      //Check for I/O error here using ferror
    }
      
  return 0;

}

int containPosition(char* from, char ch, int n)
{
  int l;
  for(l=0;l<n;l++)
    {
      if(ch==from[l])
	{ return l; }
    }

  return -1;
}
