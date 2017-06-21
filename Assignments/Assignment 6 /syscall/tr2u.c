#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
//int checkDuplicates(char* temp1, char* head1); //WRITE THIS FUNCTION                                                                                                                                           
int checkDuplicates(char* from, char* to);
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

  while((*temp2)!='\0')
    {
      m++;
      temp2++;
    }

  //Check if both are of the same size:                                                                                                                                                                          
  if(n!=m)
    {
      fprintf(stderr,"The lengths of the 2 operands must be the same\n");
      exit(1);
    }

  //Check if from has duplicate bytes:                                                                                                                                                                           
 
    if(checkDuplicates(from,to))
    {
      fprintf(stderr,"The operand from cannot have duplicate values\n");
      exit(1);
    }
    

//Now do the actual reading part
//read can have 3 values: -1,0,1 so make these cases and do
  char buf[5];
  while(read(0,buf,1) > 0)
    {
      
	  
	  int pos = containPosition(from,buf[0],n);
	  if(pos==-1)
	    write(1,buf,1);
	  else
	    {
	      buf[0] = to[pos];
	      write(1,buf,1);
	    }

	  //Check for I/O error here using ferror                                                                                   
	  }                                                     

  if(errno==-1)
     strerror(errno);
  
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







