#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
     FILE * fp;
     char * line = NULL;
     size_t len = 0;
     ssize_t nread;

     if(argc == 1)
     {
	  printf("wgrep: searchterm [file ...]\n");
	  exit(1);
     }
     else if(argc == 2)
     {
	  while((nread = getline(&line, &len, stdin)) != -1)
	       if(strstr(line, argv[1]))
		    fwrite(line, nread, 1, stdout);
	  free(line);
     }
     else
	  for(int i = 2; i < argc; i++)
	  {
	       if((fp = fopen(argv[i],"r")) == NULL)
	       {
		    printf("wgrep: cannot open file\n");
		    exit(1);
	       }
	       else
	       {
		    while((nread = getline(&line, &len, fp)) != -1)
			 if(strstr(line, argv[1]))
			      fwrite(line, nread, 1, stdout);
		    free(line);
	       }
	       fclose(fp);
	  }

     return 0;
}
      
