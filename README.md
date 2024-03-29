# Unix-Utilities
This repository holds the source code for initial projects( more exactly for unix utilities) from OSTEP https://github.com/remzi-arpacidusseau/ostep-projects. I also added a few additional unix utilities.

To compile: **make all** (you can also compile files individually).

## wcat
The program **wcat** is a simple program. Generally, it reads a file as specified by the user and prints its contents.Program **wcat** can be invoked with one or more files on the command line. It just print out each file in turn. If no files are specified on the command line, **wcat** just exit.
## wgrep
The second utility is **wgrep**, a variant of the UNIX tool **grep**. This tool looks through a file, line by line, trying to find a user-specified search term in the line. If a line has the word within it, the line is printed out, otherwise it is not. Program **wgrep** is always passed a search term and zero or more files to grep through (thus, more than one is possible). 
## wzip and wunzip
The next tools are pair, one (**wzip**) is a file compression tool, and the other (**wunzip**) is a file decompression tool. The type of compression used here is a simple form of compression called run-length encoding (RLE). RLE is quite simple: when you encounter **n** characters of the same type in a row, the compression tool (**wzip**) will turn that into the number **n** and a single instance of the character.
## pzip
The program **pzip** is multithreaded version of **wzip**. Description: https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/concurrency-pzip.
I've used threads to process multiple input files simultaneously.  However, I don't think it's a good idea to use multithreading to write such a project.
## wtee
The idea for the utility is taken from The **Linux Programming Interface**(See Exercise 4-1) https://man7.org/tlpi/. The program can accept one or more files as command line arguments or work without arguments. This distinguishes it from the program specification proposed in the book (one file as a command line argument). Also, when writing the program, I did not use the **getopt()** function. The command line option **-a** works when it is passed after the program name, but before the file name(s). You can use the program as follows: **./wtee [-a] [file] ...** 
## wcp
The idea for the utility is also taken from The **Linux Programming Interface**(See Exercise 4-2) https://man7.org/tlpi/. This is a much simplified version of the Linux **cp** command. **wcp** doesn't support command line options and therefore does not allow copying a directory to a directory. You can use this program to copy a single file to a file or directory, as well as multiple files to a directory. File holes are supported.
## wtail
The idea for the utility is also taken from The **Linux Programming Interface**(See Exercise 13-5) https://man7.org/tlpi/. This is simplified version of the Linux **tail** command that supports **-n** command line option. You can use the program as follows: **./wtail [ -n num ] file**
## Footnotes
The full description of the details of each program from OSTEP and the set of tests: https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-utilities.

If you are going to run tests, please read the instruction: https://github.com/remzi-arpacidusseau/ostep-projects#projects-for-an-operating-systems-class
