#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int cmpr=0;
int frobcmp(char const *a, char const *b)
{
  while((*a)!=' ' && (*b)!=' ')
    {
      if(*a==' ')
        return -1;
      if(*b==' ')
        return 1;
      else
        {
	  if((*a ^ 42) > (*b ^ 42))
            return 1;
	  if((*a ^ 42) < (*b ^ 42))
            return -1;
        }
      a=a+1;b=b+1;
    }
  
  return 0;
}

int compare(const void* A_1, const void* A_2)
{
  cmpr++;
  const char *a = *(const char **) A_1;
  const char *b = *(const char **) A_2;
  return (frobcmp(a,b));
}


int main()
{
  int num_words=0;
  char* array_word;
  int wordCount=0;
  int size_array=100;
  int counter;
  struct stat a;
  
  if(fstat(0,&a) < 0)  //using fstat to get info about input from stdin
    {
      fprintf(stderr,"Error produced by fstat");
      exit(1);
    }
  
  int reg = S_ISREG(a.st_mode);
  if(reg < 0)
    {
      fprintf(stderr,"File type error");
      exit(1);
    }
  else if (reg==1)
    {
      array_word=(char*)malloc(a.st_size*sizeof(char));
      if(array_word==NULL)
	{
	  fprintf(stderr,"Error in allocating memory");
	  exit(1);
	}
      
      counter = 0;
      char m[3];
      int size=a.st_size;
      while(read(0,&m,1))
        {
          if(counter==size)
            {
              array_word = realloc(array_word,size_array*sizeof(char));
              size=size*size_array;
              if(array_word==NULL)
                {fprintf(stderr, "Reallocation memory error"); exit(1);}
            }
	  
          array_word[counter]=m[0];
          //read(0,&m,1);                                                                              
          counter++;
        }
      
      
      int i;
      for(i=0;i<counter;i++)
	{
	  if(array_word[i]==' ')
	    num_words++;
	}
    }
  else
    {
      array_word=(char*)malloc(sizeof(char)*size_array);
      if(array_word==NULL)
	{
	  fprintf(stderr,"Input error");
	  exit(1);
	}
      
      counter = 0;
      char m[3];
      
      while(read(0,&m,1))
	{
	  if(counter==size_array)
	    {
	      array_word = realloc(array_word,size_array*2*sizeof(char));
	      size_array=size_array*2;
	      if(array_word==NULL)
		{fprintf(stderr, "Reallocation memory error"); exit(1);}
	    }
	  
	  if(m[0]==' ')
	    num_words++;
	  array_word[counter]=m[0];
	  //read(0,&m,1);
	  counter++;
	}
      
    }
  
  if(array_word[counter-1]!=' ')
    {
      array_word = (char*)realloc(array_word, sizeof(char)*(counter+1));
      if(array_word==NULL)
	{fprintf(stderr, "Reallocation memory error"); exit(1);}
      array_word[counter]=' ';
      counter++;
      num_words++;
    }
  //Count the number of words:
  char** words;
  words=(char**)malloc(sizeof(char*) * num_words);
  
  if(words==NULL)
    {fprintf(stderr, "Input memory allocation error");
      exit(1);}
  
  int i;
  words[wordCount]=array_word;
  for(i=0; i < counter-1; i++)
    {
      if(array_word[i]==' ')
	{ wordCount++;
	  words[wordCount] = &array_word[i+1]; }
      
    }
  wordCount++;

  //Sorting the words:
  qsort(words, num_words, sizeof(char*), compare);  
  
  char SP=' ';
  int m,d;
  //putchar(num_words);
  for(m=0; m<num_words; ++m){
    for(d=0; words[m][d]!=' '; d++){
      write(1,&words[m][d],1);}
    write(1,&SP,1);
  } 
  
  fprintf(stderr,"Comparisons: %d\n",cmpr);
  // Free all the memory that was allocated earlier
  free(array_word);
  free(words);
  
  // Program succeded successfully                                              
}
