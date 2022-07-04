# Unix-Utilities
This repository holds the source code for initial projects( more exactly for unix utilities) from OSTEP https://github.com/remzi-arpacidusseau/ostep-projects.

To compile: make all (you can also compile files individually).

## wcat
The program **wcat** is a simple program. Generally, it reads a file as specified by the user and prints its contents.Program **wcat** can be invoked with one or more files on the command line. It just print out each file in turn. If no files are specified on the command line, **wcat** just exit.
## wgrep
The second utility is **wgrep**, a variant of the UNIX tool **grep**. This tool looks through a file, line by line, trying to find a user-specified search term in the line. If a line has the word within it, the line is printed out, otherwise it is not. Program **wgrep** is always passed a search term and zero or more files to grep through (thus, more than one is possible). 
