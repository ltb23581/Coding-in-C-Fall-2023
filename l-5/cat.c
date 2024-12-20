#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 80

bool checkIfFile(char *string);

char buffer[BUFFER_SIZE];

int main(int argc, char *argv[])
{

    // initializes file descriptor and counter for command-line arguments
    int fd = STDIN_FILENO; // file descriptor
    int count = 1;         // counter for iterating through command-line arguments

    // loop through command-line arguments
    while (argc > count)
    {

        if (argc > 1)
        {
            fd = STDIN_FILENO; // rest fd to standard input

            // check if the argument is a file (ends with ".txt")
            if (checkIfFile(argv[count]))
            {

                fd = open(argv[count], O_RDONLY);

                // handles the case where opening the file fails
                if (fd == -1)
                {

                    write(STDERR_FILENO, "no file\n", 8);
                    exit(EXIT_FAILURE);
                }
            }

            count++; // move to the next command-line argument
        }

        // used to store the size of what was read
        ssize_t bytes_read;
        // reads from a standard input from a buffer up to 80 bytes with 3 parameters. The read function will also return the size of what was read into bytes_read
        // 0 means standard input
        // buffer is what buffer to read from
        // 80 means to read up to 80 bytes
        while ((bytes_read = read(fd, buffer, BUFFER_SIZE)))
        {
            // writes to a standard out to a buffer up to size bytes_read
            // 1 means standard output
            // buffer is where to store the writing
            // bytes_read is the size of the writing, in this case we want it to be the size read
            write(STDOUT_FILENO, buffer, bytes_read);
        }
    }

    if (argc == 1)
    {
        // used to store the size of what was read
        ssize_t bytes_read;
        // reads from a standard input from a buffer up to 80 bytes with 3 parameters. The read function will also return the size of what was read into bytes_read
        // 0 means standard input
        // buffer is what buffer to read from
        // 80 means to read up to 80 bytes
        while ((bytes_read = read(fd, buffer, BUFFER_SIZE)))
        {
            // writes to a standard out to a buffer up to size bytes_read
            // 1 means standard output
            // buffer is where to store the writing
            // bytes_read is the size of the writing, in this case we want it to be the size read
            write(STDOUT_FILENO, buffer, bytes_read);
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}

// function to check if a string ends with ".txt"
bool checkIfFile(char *string)
{
    char end[] = ".txt";
    int string_length = strlen(string);
    int end_length = 4;

    if (end_length > string_length)
    {
        return false; // the string is shorter than ".txt"
    }

    for (int i = 0; i < end_length; i++)
    {
        // compare characters from the end of the string and ".txt"
        if (string[string_length - i] != end[end_length - i])
        {
            return false; // mistmatch found (not a ".txt" file)
        }
    }
    return true; // the string ends with ".txt"
}
