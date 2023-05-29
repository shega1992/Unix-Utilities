#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

extern char * optarg;
extern int optind, optopt;

void print(FILE * fp, long n);

int main(int argc, char * argv[])
{
     FILE * fp;
     char * nstr = NULL, * str_end;
     long num;
     int opt;
     
     if(argc == 1)
     {
	  fprintf(stderr, "Usage: %s [ -n num ] file\n", argv[0]);
	  exit(EXIT_FAILURE);
     }

     while((opt = getopt(argc, argv, ":n:")) != -1)
     {
	  switch(opt)
	  {
	  case 'n':
	       nstr = optarg;
	       break;
	  case ':':
	       fprintf(stderr, "Missing argument for %c\n", optopt);
	       exit(EXIT_FAILURE);
	  case '?':
	       fprintf(stderr, "Unrecognized option %c\n", optopt);
	       exit(EXIT_FAILURE);
	  }
     }

     if(!nstr)
     {
	  if((fp = fopen(argv[1], "r")) == NULL)
	  {
	       fprintf(stderr, "Couldn't open %s : %s\n", argv[1], strerror(errno));
	       exit(EXIT_FAILURE);
	  }
	  print(fp, 10);
	  if(fclose(fp) != 0)
	  {
	       fprintf(stderr, "Couldn't close %s : %s\n", argv[1], strerror(errno));
	       exit(EXIT_FAILURE);
	  }
     }
     else if((num = strtol(nstr, &str_end, 10)))
     {
	  if((fp = fopen(argv[optind], "r")) == NULL)
	  {
	       fprintf(stderr, "Couldn't open %s : %s\n", argv[optind], strerror(errno));
	       exit(EXIT_FAILURE);
	  }
	  print(fp, num);
	  if(fclose(fp) != 0)
	  {
	       fprintf(stderr, "Couldn't close %s : %s\n", argv[optind], strerror(errno));
	       exit(EXIT_FAILURE);
	  }
     }
     else
     {
	  fprintf(stderr, "Incorrent argument for %s option\n", argv[1]);
	  exit(EXIT_FAILURE);
     }
     	       
     return 0;
}

void print(FILE * fp, long n)
{
     char * line = NULL;
     size_t len = 0;
     ssize_t nread;
     int count = 0;

     while ((nread = getline(&line, &len, fp)) != -1)
	  count++;

     if(errno)
     {
	  fprintf(stderr, "Couldn't read a line : %s\n", strerror(errno));
	  exit(EXIT_FAILURE);
     }

     rewind(fp);

     if(count <= n)
     {
	  while ((nread = getline(&line, &len, fp)) != -1)
	       if(write(STDOUT_FILENO, line, nread) != nread)
	       {
		    fprintf(stderr, "Couldn't write whole buffer to standard output\n");
		    exit(EXIT_FAILURE);
	       }

	  if(errno)
	  {
	       fprintf(stderr, "Couldn't read a line : %s\n", strerror(errno));
	       exit(EXIT_FAILURE);
	  }
     }
     else
     {
	  for(int i = 0; i < count - n && (nread = getline(&line, &len, fp)) != -1; i++)
	       ;

	  if(errno)
	  {
	       fprintf(stderr, "Couldn't read a line : %s\n", strerror(errno));
	       exit(EXIT_FAILURE);
	  }

	  while ((nread = getline(&line, &len, fp)) != -1)
	       if(write(STDOUT_FILENO, line, nread) != nread)
	       {
		    fprintf(stderr, "Couldn't write whole buffer to standard output\n");
		    exit(EXIT_FAILURE);
	       }

	  if(errno)
	  {
	       fprintf(stderr, "Couldn't read a line : %s\n", strerror(errno));
	       exit(EXIT_FAILURE);
	  }
     }

     free(line);
}
