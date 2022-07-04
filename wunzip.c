#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
     FILE * fp;
     unsigned int num_of_occur;
     char ch;

     if(argc == 1)
     {
	  printf("wunzip: file1 [file2 ...]\n");
	  exit(1);
     }
     else
     {
	  for(int i = 1; i < argc; i++)
	  {
	       if((fp = fopen(argv[i], "rb")) == NULL)
	       {
		    printf("wunzip: cannot open file\n");
		    exit(1);
	       }
	       else
		    while(fread(&num_of_occur, sizeof(unsigned int), 1, fp))
		    {
			 fread(&ch, sizeof(char), 1, fp);
			 for(int j = 0; j < num_of_occur; j++)
			      putchar(ch);
		    }
	       fclose(fp);
	  }
     }

     return 0;
}
			 
