#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#ifdef __GNUC__

    /* This macro stops 'gcc -Wall' complaining that "control reaches
       end of non-void function" if we use the following functions to
       terminate main() or some other non-void function. */

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

void FileToFile(int argc , char **  argv , int * inputFd , int outputFd) NORETURN;
void FileToDirectory(int argc , char **  argv , int * inputFd , int outputFd) NORETURN;

int main(int argc, char * argv[])
{
     int * inputFd;
     int outputFd;

     if(argc < 3)
     {
	  fprintf(stderr, "Usage:\n\t%s SRC_FILE DEST_FILE" 
		  "\n\t%s SRC_FILE... DIRECTORY\n", argv[0], argv[0]);
	  exit(EXIT_FAILURE);
     }

     inputFd = calloc(argc - 2, sizeof(int));
     if(inputFd == NULL)
     {
	  fputs("Couldn't allocate the memory\n", stderr);
	  exit(EXIT_FAILURE);
     }

     for(int i = 0; i < argc - 2; i++)
	  if((inputFd[i] = open(argv[i + 1], O_RDWR)) == -1)
	  {
	       fprintf(stderr, "Couldn't open %s : %s\n", argv[i + 1], strerror(errno));
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }

     if(argc == 3)
     {
	  if((outputFd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1)
	  {
	       if(errno == EISDIR)
		    FileToDirectory(argc, argv, inputFd, outputFd);
	       else
	       {
		    fprintf(stderr, "Couldn't open %s : %s\n", argv[argc - 1], strerror(errno));
		    free(inputFd);
		    exit(EXIT_FAILURE);
	       }
	  }
	  else
	       FileToFile(argc, argv, inputFd, outputFd);
     }
     else if(opendir(argv[argc - 1]) == NULL)
     {
	  if(errno == ENOTDIR)
	  {
	       fprintf(stderr, "%s is not directory\n", argv[argc - 1]);
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }
	  else if(errno == ENOENT)
	  {
	       fprintf(stderr, "%s directory doesn't exist\n", argv[argc - 1]);
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }
	  else
	  {
	       fprintf(stderr, "Couldn't open %s directory\n", argv[argc - 1]);
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }
     }
     else
	  FileToDirectory(argc, argv, inputFd, -1);
     
}

void FileToFile(int argc , char **  argv , int * inputFd , int outputFd)
{
     ssize_t numRead;
     char * buf;
     struct stat sb;

     if(stat(argv[1], &sb) == -1)
     {
	  fprintf(stderr, "Couldn't get information about a file %s : %s\n", argv[1], strerror(errno));
	  free(inputFd);
	  exit(EXIT_FAILURE);
     }

     buf = malloc(sb.st_size);
     if(buf == NULL)
     {
	  fputs("Couldn't allocate the memory\n", stderr);
	  free(inputFd);
	  exit(EXIT_FAILURE);
     }

     while((numRead = read(inputFd[0], buf, sb.st_size)) > 0)
	  if(write(outputFd, buf, numRead) != numRead)
	  {
	       fprintf(stderr, "Couldn't write whole buffer to %s\n", argv[argc - 1]);
	       free(buf);
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }
	  
     if(numRead == -1)
     {
	  fprintf(stderr, "read : %s\n", strerror(errno));
	  free(buf);
	  free(inputFd);
	  exit(EXIT_FAILURE);
     }

     if(close(inputFd[0]) == -1)
     {
	  fprintf(stderr, "Couldn't close %s : %s\n", argv[1], strerror(errno));
	  free(buf);
	  free(inputFd);
	  exit(EXIT_FAILURE);
     }
	       
     if(close(outputFd == -1))
     {
	  fprintf(stderr, "Couldn't close %s : %s\n", argv[argc - 1], strerror(errno));
	  free(buf);
	  free(inputFd);
	  exit(EXIT_FAILURE);
     }

     free(buf);
     free(inputFd);

     exit(EXIT_SUCCESS);
}

void FileToDirectory(int argc , char **  argv , int * inputFd , int outputFd)
{
     ssize_t numRead;
     char * buf, * path;
     struct stat sb;

     for(int i = 0; i < argc - 2; i++)
     {
	  if(stat(argv[i + 1], &sb) == -1)
	  {
	       fprintf(stderr, "Couldn't get information about a file %s : %s\n", argv[i + 1], strerror(errno));
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }

	  buf = malloc(sb.st_size);
	  if(buf == NULL)
	  {
	       fputs("Couldn't allocate the memory\n", stderr);
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }

	  path = malloc(strlen(argv[argc - 1]) + strlen(argv[i + 1]) + 2); // + 2 for / and \0
	  if(path == NULL)
	  {
	       fputs("Couldn't allocate the memory\n", stderr);
	       free(buf);
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }
	  strcpy(path, argv[argc - 1]);
	  strcat(path, "/");
	  strcat(path, argv[i + 1]);
	  
	  if((outputFd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1)
	  {
	       fprintf(stderr, "Couldn't open %s : %s\n", path, strerror(errno));
	       free(path);
	       free(buf);
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }

	  while((numRead = read(inputFd[i], buf, sb.st_size)) > 0)
	       if(write(outputFd, buf, numRead) != numRead)
	       {
		    fprintf(stderr, "Couldn't write whole buffer to %s\n", path);
		    free(path);
		    free(buf);
		    free(inputFd);
		    exit(EXIT_FAILURE);
	       }
	  
	  if(numRead == -1)
	  {
	       fprintf(stderr, "read : %s\n", strerror(errno));
	       free(path);
	       free(buf);
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }

	  if(close(inputFd[i]) == -1)
	  {
	       fprintf(stderr, "Couldn't close %s : %s\n", argv[i], strerror(errno));
	       free(path);
	       free(buf);
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }
	       
	  if(close(outputFd == -1))
	  {
	       fprintf(stderr, "Couldn't close %s : %s\n", path, strerror(errno));
	       free(path);
	       free(buf);
	       free(inputFd);
	       exit(EXIT_FAILURE);
	  }

	  free(buf);
	  free(path);
     }

     free(inputFd);
     exit(EXIT_SUCCESS);
}

	  
		 
	  
