#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
  FILE * fp;
  int ch;

  for(int i = 1; i < argc; i++)
  {
       if((fp = fopen(argv[i], "r")) == NULL)
       {
	    printf("wcat: cannot open file\n");
	    exit(1);
       }
       else
	    while((ch = getc(fp)) != EOF)
		 putc(ch, stdout);
       fclose(fp);
  }

  return 0;
}
