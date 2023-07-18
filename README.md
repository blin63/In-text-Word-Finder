## In-text Word Finder

**NOTE: This program was written for a past school assignment
while learning how to code in C**

### Special Execution Instructions

This program accepts two command line arguments in
this format: ```TextFileName WordToFind```

when executing this program, ensure that these
two command line arguments are supplied in order for
the program to run.

On the command line, the command to run the program executable
should look similiar to this:

```./In-text_Word_Finder.exe fileName.txt wordToFind```

If using a IDE to run the executable, ensure that the appropriate
command line arguments shown above are added to the
Run configurations before running the program.

### Program Description

This program accepts two command line arguments;
the text file and the word to search for in the text file.

When the first occurance of the word to search for is found,
the program will stop running and display the location
of the target word by displaying the line number and character
number of the target word.

If the word to search for cannot be found, a message will pop up
displaying that the targeted word could not be found upon program
termination.