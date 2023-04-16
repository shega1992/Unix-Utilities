#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int main(int argc, char * argv[])
{
     ssize_t numRead;
     int * fd;
     char buf[BUF_SIZE];
     
     if(argc == 1)
     {
	  while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
	  {
	       if(write(STDOUT_FILENO, buf, numRead) != numRead)
	       {
		    fputs("Couldn't write whole buffer to standard output\n", stderr);
		    exit(EXIT_FAILURE);
	       }
	  }
	  
	  if(numRead == -1)
	  {
	       fprintf(stderr, "read : %s\n", strerror(errno));
	       exit(EXIT_FAILURE);
	  }
     }
     else if(!strcmp(argv[1], "-a"))
     {
	  fd = calloc(argc - 2, sizeof(int));
	  if(fd == NULL)
	  {
	       fputs("Couldn't allocate the memory\n", stderr);
	       exit(EXIT_FAILURE);
	  }
	  
	  for(int i = 0; i < argc - 2; i++)
	       if((fd[i] = open(argv[i + 2], O_WRONLY | O_CREAT | O_APPEND, 0664)) == -1)
	       {
		    fprintf(stderr, "Couldn't open %s : %s\n", argv[i + 2], strerror(errno));
		    exit(EXIT_FAILURE);
	       }

	  while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
	  {
	       if(write(STDOUT_FILENO, buf, numRead) != numRead)
	       {
		    fputs("Couldn't write whole buffer to standard output\n", stderr);
		    exit(EXIT_FAILURE);
	       }
	       
	       for(int i = 0; i < argc - 2; i++)
		    if(write(fd[i], buf, numRead) != numRead)
		    {
			 fprintf(stderr, "Couldn't write whole buffer to %s\n", argv[i + 2]);
			 exit(EXIT_FAILURE);
		    }
	  }

	  if(numRead == -1)
	  {
	       fprintf(stderr, "read : %s\n", strerror(errno));
	       exit(EXIT_FAILURE);
	  }
	  for(int i = 0; i < argc - 2; i++)
	       if(close(fd[i]) == -1)
	       {
		    fprintf(stderr, "Couldn't close %s : %s\n", argv[i + 2], strerror(errno));
		    exit(EXIT_FAILURE);
	       }
	       

	  free(fd);
     }
     else
     {
	  fd = calloc(argc - 1, sizeof(int));
	  if(fd == NULL)
	  {
	       fputs("Couldn't allocate the memory\n", stderr);
	       exit(EXIT_FAILURE);
	  }
	  
	  for(int i = 0; i < argc - 1; i++)
	       if((fd[i] = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1)
	       {
		    fprintf(stderr, "Couldn't open %s : %s\n", argv[i + 1], strerror(errno));
		    exit(EXIT_FAILURE);
	       }
	  
	  while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
	  {
	       if(write(STDOUT_FILENO, buf, numRead) != numRead)
	       {
		    fputs("Couldn't write whole buffer to standard output\n", stderr);
		    exit(EXIT_FAILURE);
	       }
	       
	       for(int i = 0; i < argc - 1; i++)
		    if(write(fd[i], buf, numRead) != numRead)
		    {
			 fprintf(stderr, "Couldn't write whole buffer to %s\n", argv[i + 1]);
			 exit(EXIT_FAILURE);
		    }
	  }

	  if(numRead == -1)
	  {
	       fprintf(stderr, "read : %s\n", strerror(errno));
	       exit(EXIT_FAILURE);
	  }
	  for(int i = 0; i < argc - 1; i++)
	       if(close(fd[i]) == -1)
	       {
		    fprintf(stderr, "Couldn't close %s : %s\n", argv[i + 1], strerror(errno));
		    exit(EXIT_FAILURE);
	       }

	  free(fd);
     }

     return 0;
		    
}

      


		
		
		     
	  
